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
#include "Player.h"
#include <QJsonObject>

Game::Game(QObject *parent) :
	QObject{parent},
	_board{new Board(this)},
	_dice{new Dice(this)},
	_currentPlayerId{0}
{
	for (int id{0}; id < 4; id++) {
		auto *player{new Player(id, this)};

		_players.append(player);

		connect(player, &Player::pawnsCountChanged,
				this, &Game::onPawnsCountChanged);
	}

	connect(_board, &Board::playerEscaped, this, &Game::onPlayerEscaped);
}

QJsonObject Game::boardLayout() const
{
	return _board->boardLayout();
}

void Game::rollDice()
{
	_dice->roll();

	emit diceRolled(_dice->score());
	emit bringInChanged(canBringIn());
	emit possibleMoves(_board->findPossibleMoves(_currentPlayerId, _dice->score()));
}

void Game::bringPawnIn()
{
	if (_board->bringPawnIn(_players.at(_currentPlayerId)->takePawn()))
		advance();
}

void Game::movePawn(int srcField)
{
	if (_board->movePawn(_currentPlayerId, srcField, _dice->score()))
		advance();
}

void Game::advance()
{
	if (_dice->score() != 6)
		switchToNextPlayer();

	emit nextTurn(_currentPlayerId);
}

void Game::reset()
{
	_board->reset();
	_escapedPlayers.clear();
	_currentPlayerId = 0;

	for (auto *player : std::as_const(_players))
		player->reset();

	emit nextTurn(_currentPlayerId);
}

void Game::switchToNextPlayer()
{
	if (++_currentPlayerId == _players.count())
		_currentPlayerId = 0;

	if (_escapedPlayers.contains(_players.at(_currentPlayerId)))
		switchToNextPlayer();
}

bool Game::canBringIn() const
{
	return _dice->score() == 6
		   && _players.at(_currentPlayerId)->pawnsCount()
		   && _board->checkBringIn(_currentPlayerId);
}

void Game::onPawnsCountChanged()
{
    auto *player{static_cast<Player *>(sender())};

	emit pawnCountChanged(player->id(), player->pawnsCount());
}

void Game::onPlayerEscaped(int playerId)
{
	_escapedPlayers.append(_players.at(playerId));
	_escapedPlayers.count() == 3 ? emit gameOver() : emit playerWon(playerId);
}
