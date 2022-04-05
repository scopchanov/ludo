#include "Pawn.h"

Pawn::Pawn(int playerId, QObject *parent) :
	QObject{parent},
	m_playerId(playerId)
{

}

int Pawn::playerId() const
{
	return m_playerId;
}

void Pawn::bust()
{
	emit busted();
}
