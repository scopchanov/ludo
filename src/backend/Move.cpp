/**
MIT License

Copyright (c) 2022-2025 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Move.h"
#include "Path.h"
#include "Tile.h"
#include "Pawn.h"
#include "Board.h"

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

	if (exceedsTrackLength())
		takePawnOut();
	else
		movePawn();

	return true;
}

void Move::movePawn()
{
	int playerId{_pawn->playerId()};
	int index{wrappedIndex(_board->entryTileIndex(playerId) + _pawn->trip())};

	_board->_track->movePawn(index, _steps);
}

void Move::takePawnOut()
{

}

bool Move::exceedsTrackLength() const
{
	return _pawn->trip() + _steps > _board->_track->tileCount();
}

Tile *Move::trackTile() const
{
	int playerId{_pawn->playerId()};
	int tileIndex{wrappedIndex(_board->entryTileIndex(playerId) + _pawn->trip() + _steps)};

	return _board->_track->tile(tileIndex);
}

Tile *Move::homeTile() const
{
	int tileIndex{wrappedIndex(_pawn->trip() + _steps)};

	return _board->_homeAreas.at(_pawn->playerId())->tile(tileIndex);
}

int Move::wrappedIndex(int index) const
{
	return index % _board->_track->tileCount();
}
