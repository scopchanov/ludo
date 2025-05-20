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
	for (int n{0}; n < 4; n++) {
        auto *player{new Player(n, this)};

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
	emit bringInChanged(_dice->score() == 6
						&& _players.at(_currentPlayerId)->pawnsCount()
						&& _board->checkBringIn(_currentPlayerId));
	emit possibleMoves(_board->findPossibleMoves(_dice->score(),
												  _currentPlayerId));
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
}

void Game::switchToNextPlayer()
{
	if (++_currentPlayerId == _players.count())
		_currentPlayerId = 0;

	if (_escapedPlayers.contains(_players.at(_currentPlayerId)))
		switchToNextPlayer();
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
