#include "Game.h"
#include "Board.h"
#include "Dice.h"
#include "Pawn.h"
#include "Player.h"
#include "Field.h"
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

	connect(m_board, &Board::moveMade, this, &Game::advance);
}

QList<QPair<int, int>> Game::boardLayout() const
{
	QList<QPair<int, int>> pawns;

	for (int n = 0; n < 40; n++) {
		auto *pawn = m_board->field(n)->pawn();

		if (pawn)
			pawns.append(QPair<int, int>{n, pawn->playerId()});
	}

	return pawns;
}

void Game::rollDice()
{
	m_dice->roll();

	emit diceRolled(m_dice->score());
	emit canBringOn(checkBringIn(m_dice->score()));
	emit possibleMoves(findPossibleMoves(m_dice->score()));
}

void Game::bringPawnOn()
{
	m_board->bringPawnOn(m_players.at(m_currentPlayerId)->takePawn(),
						 toBoardCoordinates(0));
}

void Game::movePawn(int srcField)
{
	m_board->movePawn(srcField, m_dice->score());
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

}

bool Game::checkBringIn(int score) const
{
	auto *pawn = m_board->field(toBoardCoordinates(0))->pawn();

	return score == 6 && m_players.at(m_currentPlayerId)->pawnsCount()
			&& (!pawn || pawn->playerId() != m_currentPlayerId);
}

QList<int> Game::findPossibleMoves(int score) const
{
	QList<int> moves;

	for (int n = 0; n < 40; n++) {
		auto *srcPawn = m_board->field(n)->pawn();

		if (srcPawn && srcPawn->playerId() == m_currentPlayerId) {
			int dst = n + score;

			if (dst >= 40)
				dst -= 40;

			auto *dstPawn = m_board->field(dst)->pawn();

			if (!(dstPawn && dstPawn->playerId() == m_currentPlayerId))
				moves.append(n);
		}
	}

	return moves;
}

int Game::toBoardCoordinates(int fieldNumber) const
{
	return 10*m_currentPlayerId + fieldNumber;
}

void Game::onPawnsCountChanged()
{
	auto *player = static_cast<Player *>(sender());

	emit pawnCountChanged(player->id(), player->pawnsCount());
}
