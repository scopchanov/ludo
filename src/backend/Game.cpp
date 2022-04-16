#include "Game.h"
#include "Dice.h"
#include "Board.h"
#include "Pathway.h"
#include "Pawn.h"
#include "Field.h"
#include "Player.h"
#include <QJsonObject>
#include <QDebug>

Game::Game(QObject *parent) :
	QObject{parent},
	m_board{new Board(this)},
	m_dice{new Dice(this)},
	m_currentPlayerId{0}
{
	for (int n = 0; n < 4; n++) {
		auto *player = new Player(n, this);

		m_players.append(player);

		connect(player, &Player::pawnsCountChanged,
				this, &Game::onPawnsCountChanged);
	}

	connect(m_board, &Board::playerWins, this, &Game::playerWins);
}

QJsonObject Game::boardLayout() const
{
	return m_board->boardLayout();
}

void Game::rollDice()
{
	m_dice->roll();

	emit diceRolled(m_dice->score());
	emit bringInChanged(m_dice->score() == 6
						&& m_players.at(m_currentPlayerId)->pawnsCount()
						&& m_board->checkBringIn(m_currentPlayerId));
	emit possibleMoves(m_board->findPossibleMoves(m_dice->score(),
												  m_currentPlayerId));
}

void Game::bringPawnIn()
{
	if (m_board->bringPawnIn(m_players.at(m_currentPlayerId)->takePawn()))
		advance();
}

void Game::movePawn(int srcField)
{
	if (m_board->movePawn(m_currentPlayerId, srcField, m_dice->score()))
		advance();
}

void Game::advance()
{
	if (m_dice->score() != 6)
		if (++m_currentPlayerId >= m_players.count())
			m_currentPlayerId = 0;

	emit nextTurn(m_currentPlayerId);
}

void Game::reset()
{
//	m_board
}

void Game::onPawnsCountChanged()
{
	auto *player = static_cast<Player *>(sender());

	emit pawnCountChanged(player->id(), player->pawnsCount());
}
