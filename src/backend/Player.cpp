#include "Player.h"
#include "Pawn.h"

Player::Player(int playerId, QObject *parent) :
	QObject{parent},
	_id{playerId}
{
	for (int n{0}; n < 4; n++) {
        auto *pawn{new Pawn(playerId, this)};

		_pawns.append(pawn);

		connect(pawn, &Pawn::busted, this, &Player::onPawnBusted);
	}
}

int Player::id() const
{
	return _id;
}

int Player::pawnsCount() const
{
	return _pawns.count();
}

Pawn *Player::takePawn()
{
	if (_pawns.isEmpty())
		return nullptr;

	auto *pawn = _pawns.takeLast();

	emit pawnsCountChanged();

	return pawn;
}

void Player::reset()
{

}

void Player::onPawnBusted()
{
	qDebug("saram rasam");
	_pawns.append(static_cast<Pawn *>(sender()));

	emit pawnsCountChanged();
}
