#include "Player.h"
#include "Pawn.h"

Player::Player(int playerId, QObject *parent) :
	QObject{parent},
	m_id{playerId}
{
	for (int n{0}; n < 4; n++) {
        auto *pawn{new Pawn(playerId, this)};

		m_pawns.append(pawn);

		connect(pawn, &Pawn::busted, this, &Player::onPawnBusted);
	}
}

int Player::id() const
{
	return m_id;
}

int Player::pawnsCount() const
{
	return m_pawns.count();
}

Pawn *Player::takePawn()
{
	if (m_pawns.isEmpty())
		return nullptr;

	auto *pawn = m_pawns.takeLast();

	emit pawnsCountChanged();

	return pawn;
}

void Player::reset()
{

}

void Player::onPawnBusted()
{
	qDebug("saram rasam");
	m_pawns.append(static_cast<Pawn *>(sender()));

	emit pawnsCountChanged();
}
