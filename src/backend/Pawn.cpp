#include "Pawn.h"

Pawn::Pawn(int playerId, QObject *parent) :
	QObject{parent},
	_playerId(playerId),
	_traveledDistance{0}
{

}

int Pawn::playerId() const
{
	return _playerId;
}

int Pawn::traveledDistance() const
{
	return _traveledDistance;
}

void Pawn::increaseTraveledDistance(int fieldCount)
{
	_traveledDistance += fieldCount;
}

void Pawn::bust()
{
	_traveledDistance = 0;

	emit busted();
}
