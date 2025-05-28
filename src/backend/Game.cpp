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

QJsonObject Game::state() const
{
	return _board->state();
}

void Game::setState(const QJsonObject &json)
{

}

void Game::rollDice()
{
	_dice->roll();

	QList<int> moves{_board->findPossibleMoves(_currentPlayerId, _dice->score())};
	bool canBringPawnIn{canBringIn()};

	emit diceRolled(_dice->score());
	emit bringInChanged(canBringPawnIn);
	emit possibleMoves(moves);

	if (!canBringPawnIn && moves.isEmpty())
		advance();
}

void Game::bringPawnIn()
{
	if (_board->bringPawnIn(_players.at(_currentPlayerId)->takePawn()))
		advance();
}

void Game::movePawn(int srcTileIndex)
{
	if (_board->movePawn(_currentPlayerId, srcTileIndex, _dice->score()))
		advance();
}

void Game::reset()
{
	_board->reset();
	_winners.clear();
	_currentPlayerId = 0;

	for (auto *player : std::as_const(_players))
		player->reset();

	emit nextTurn(_currentPlayerId);
}

void Game::advance()
{
	if (_dice->score() != 6)
		switchToNextPlayer();

	emit nextTurn(_currentPlayerId);
}

void Game::switchToNextPlayer()
{
	_currentPlayerId++;
	_currentPlayerId %= _players.count();

	if (_winners.contains(_players.at(_currentPlayerId)))
		switchToNextPlayer();
}

bool Game::canBringIn() const
{
	return _dice->score() == 6
		   && _players.at(_currentPlayerId)->pawnsCount()
		   && _board->canBringIn(_players.at(_currentPlayerId)->pawn(0));
}

void Game::onPawnsCountChanged()
{
    auto *player{static_cast<Player *>(sender())};

	emit pawnCountChanged(player->id(), player->pawnsCount());
}

void Game::onPlayerEscaped(int playerId)
{
	_winners.append(_players.at(playerId));
	_winners.count() == 3 ? emit gameOver() : emit playerWon(playerId);
}
