#include "Pawn.h"

Pawn::Pawn(int playerId, QObject *parent) :
	QObject{parent},
	m_playerId(playerId),
	m_traveledDistance{0}
{

}

int Pawn::playerId() const
{
	return m_playerId;
}

int Pawn::traveledDistance() const
{
	return m_traveledDistance;
}

void Pawn::increaseTraveledDistance(int fieldCount)
{
	m_traveledDistance += fieldCount;
}

void Pawn::bust()
{
	m_traveledDistance = 0;

	emit busted();
}
