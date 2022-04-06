#include "Game.h"
#include "Board.h"
#include "Dice.h"
#include "Pawn.h"
#include "Player.h"
#include "Field.h"

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

	int score{m_dice->score()};
	auto *pawn{m_board->field(toBoardCoordinates(0))->pawn()};
	bool isBringOnPossible = score == 6
			&& m_players.at(m_currentPlayerId)->pawnsCount()
			&& (!pawn || pawn->playerId() != m_currentPlayerId);
	QList<int> moves;

	for (int n = 0; n < 40; n++) {
		auto *pawn = m_board->field(n)->pawn();

		if (pawn && pawn->playerId() == m_currentPlayerId)
			moves.append(n);
	}

	emit diceRolled(score);
	emit canBringOn(isBringOnPossible);
	emit possibleMoves(moves);
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
	if (++m_currentPlayerId >= m_players.count())
		m_currentPlayerId = 0;

	emit nextTurn(m_currentPlayerId);
}

void Game::reset()
{

}

int Game::toBoardCoordinates(int fieldNumber) const
{
	return 10*m_currentPlayerId + fieldNumber;
}

int Game::toPlayerCoordinates(int fieldNumber) const
{
	return fieldNumber - 10*m_currentPlayerId;
}

void Game::onPawnsCountChanged()
{
	auto *player = static_cast<Player *>(sender());

	emit pawnCountChanged(player->id(), player->pawnsCount());
}
