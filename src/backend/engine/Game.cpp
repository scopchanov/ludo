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
#include "Game_p.h"
#include "Dice.h"
#include "Board.h"
#include "Path.h"
#include "actions/BringInAction.h"
#include "actions/MoveAction.h"
#include "utils/GameSerializer.h"
#include <QJsonObject>
#include <QJsonArray>

Game::Game(QObject *parent) :
	QObject{parent},
	_ptr{new GamePrivate(this)}
{
	connect(_ptr->board, &Board::playerEscaped, this, &Game::onPlayerEscaped);
}

Game::~Game()
{
	delete _ptr;
}

QJsonObject Game::state() const
{
	return GameSerializer(_ptr).serialize();
}

void Game::setState(const QJsonObject &json)
{
	GameSerializer(_ptr).deserialize(json);

	emit stateChanged();
	_ptr->advance();
}

int Game::currentplayer() const
{
	return _ptr->currentplayer;
}

bool Game::canBringIn() const
{
	BringInAction action(_ptr->board, _ptr->currentplayer);

	return _ptr->rolledSix() && action.isPossible();
}

QList<int> Game::possibleMoves()
{
	return _ptr->findPossibleMoves();
}

void Game::rollDice()
{
	if (_ptr->isGameOver())
		return;

	_ptr->dice->roll();

	emit diceRolled(_ptr->dice->score());

	if (!canBringIn() && possibleMoves().isEmpty())
		_ptr->advance();
}

void Game::bringPawnIn()
{
	BringInAction action(_ptr->board, _ptr->currentplayer);

	if (!_ptr->rolledSix() || !action.take())
		return;

	emit stateChanged();
	_ptr->advance();
}

void Game::movePawn(int srcTileIndex)
{
	int score{_ptr->dice->score()};
	MoveAction action(_ptr->board, _ptr->currentplayer, srcTileIndex, score);

	if (!action.take())
		return;

	emit stateChanged();
	_ptr->advance();
}

void Game::init()
{
	_ptr->board->init();
	emit stateChanged();
}

void Game::reset()
{
	_ptr->winners.clear();
	_ptr->board->clear();
	_ptr->currentplayer = 0;

	emit nextTurn(_ptr->currentplayer);
}

void Game::onPlayerEscaped(int player)
{
	_ptr->winners.append(player);
	emit playerEscaped(player);

	if (_ptr->isGameOver())
		emit gameOver();
}

GamePrivate::GamePrivate(Game *parent) :
	parent{parent},
	dice{new Dice(parent)},
	board{new Board(parent)},
	playerCount{4},
	currentplayer{0}
{

}

void GamePrivate::advance()
{
	if (!rolledSix())
		switchToNextPlayer();

	emit parent->nextTurn(currentplayer);
}

void GamePrivate::switchToNextPlayer()
{
	currentplayer++;
	currentplayer %= playerCount;

	if (winners.contains(currentplayer))
		switchToNextPlayer();
}

QList<int> GamePrivate::findPossibleMoves()
{
	QList<int> moves;

	for (int tileIndex{0}; tileIndex < board->track()->tileCount(); tileIndex++)
		if (MoveAction(board, currentplayer, tileIndex, dice->score()).isPossible())
			moves.append(tileIndex);

	return moves;
}

bool GamePrivate::rolledSix() const
{
	return dice->score() == 6;
}

bool GamePrivate::isGameOver() const
{
	return winners.count() == playerCount - 1;
}
