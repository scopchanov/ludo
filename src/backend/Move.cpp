#include "Move.h"
#include "Path.h"
#include "Tile.h"
#include "Pawn.h"
#include "Board.h"

#define PLAYER_OFFSET 10

Move::Move(Pawn *pawn, int steps, Board *parent) :
	QObject{parent},
	_board{parent},
	_pawn{pawn},
	_steps{steps}
{

}

bool Move::isPossible() const
{
	return _pawn->canOccupy(exceedsTrackLength() ? homeTile() : trackTile());
}

bool Move::make()
{
	if (!isPossible())
		return false;

	// TODO - make move

	return true;
}

bool Move::exceedsTrackLength() const
{
	return _pawn->trip() + _steps > _board->_track->tileCount();
}

Tile *Move::trackTile() const
{
	int playerId{_pawn->playerId()};
	int tileIndex{wrappedIndex(entryTile(playerId) + _pawn->trip() + _steps)};

	return _board->_track->tile(tileIndex);
}

Tile *Move::homeTile() const
{
	int tileIndex{wrappedIndex(_pawn->trip() + _steps)};

	return _board->_homeAreas.at(_pawn->playerId())->tile(tileIndex);
}

int Move::entryTile(int playerId) const
{
	return playerId*PLAYER_OFFSET;
}

int Move::wrappedIndex(int index) const
{
	return index % _board->_track->tileCount();
}
