/**
MIT License

Copyright (c) 2022-2025 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Game.h"
#include "Dice.h"
#include "Board.h"
#include "BoardSerializer.h"
#include <QJsonObject>
#include <QJsonArray>

Game::Game(QObject *parent) :
	QObject{parent},
	_dice{new Dice(this)},
	_board{new Board(this)},
	_playerCount{4},
	_currentplayer{0}
{
	connect(_board, &Board::playerEscaped, this, &Game::onPlayerEscaped);
}

QJsonObject Game::state() const
{
	return QJsonObject{{"currentPlayer", _currentplayer},
					   {"score", _dice->score()},
					   {"board", BoardSerializer::toJson(_board)}};
}

void Game::setState(const QJsonObject &json)
{
	BoardSerializer::fromJson(_board, json.value("board").toObject());

	_currentplayer = json.value("currentPlayer").toInt();
	_dice->setScore(json.value("score").toInt());

	emit stateChanged();
	advance();
}

int Game::currentplayer() const
{
	return _currentplayer;
}

bool Game::canBringIn() const
{
	return _dice->score() == 6 && _board->canBringIn(_currentplayer);
}

QList<int> Game::possibleMoves() const
{
	return _board->findPossibleMoves(_currentplayer, _dice->score());
}

void Game::rollDice()
{
	_dice->roll();

	QList<int> moves{_board->findPossibleMoves(_currentplayer, _dice->score())};
	bool canBringPawnIn{canBringIn()};

	emit diceRolled(_dice->score());

	if (!canBringPawnIn && moves.isEmpty())
		advance();
}

void Game::bringPawnIn()
{
	if (!_board->bringPawnIn(_currentplayer))
		return;

	emit stateChanged();
	advance();
}

void Game::movePawn(int srcTileIndex)
{
	if (!_board->movePawn(_currentplayer, srcTileIndex, _dice->score()))
		return;

	emit stateChanged();
	advance();
}

void Game::init()
{
	_board->init();
	emit stateChanged();
}

void Game::reset()
{
	_winners.clear();
	_board->clear();
	_currentplayer = 0;

	emit nextTurn(_currentplayer);
}

void Game::advance()
{
	if (_dice->score() != 6)
		switchToNextPlayer();

	emit nextTurn(_currentplayer);
}

void Game::switchToNextPlayer()
{
	_currentplayer++;
	_currentplayer %= _playerCount;

	if (_winners.contains(_currentplayer))
		switchToNextPlayer();
}

void Game::onPlayerEscaped(int player)
{
	_winners.append(player);
	emit playerEscaped(player);

	if (_winners.count() == _playerCount - 1)
		emit gameOver();
}
