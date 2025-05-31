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

#include "MoveAction.h"
#include "../Board.h"
#include "../Path.h"

MoveAction::MoveAction(Board *board, int player, int srcTileIndex, int steps) :
	AbstractGameAction{board, player},
	_srcTileIndex{srcTileIndex},
	_steps{steps}
{

}

bool MoveAction::isPossible() const
{
	if (!board()->track()->isTileOccupiedBy(player(), _srcTileIndex))
		return false;

	return exceedsTrackLength() ? canEscape() : canMove();
}

bool MoveAction::trigger()
{
	if (!isPossible())
		return false;

	if (exceedsTrackLength())
		escapePawn();
	else
		movePawn();

	return true;
}

void MoveAction::movePawn()
{
	board()->track()->movePawn(player(), _srcTileIndex, _steps);
}

void MoveAction::escapePawn()
{
	int tileIndex{destinationTileIndex() % board()->track()->tileCount()};

	board()->track()->removePlayerAt(_srcTileIndex);
	board()->homeArea(player())->bringPawnIn(player(), tileIndex);
}

bool MoveAction::canMove() const
{
	return board()->track()->canMove(player(), _srcTileIndex, _steps);
}

bool MoveAction::canEscape() const
{
	int tileIndex{destinationTileIndex() % board()->track()->tileCount()};

	return board()->homeArea(player())->canBringPawnIn(player(), tileIndex);
}

bool MoveAction::exceedsTrackLength() const
{
	return destinationTileIndex() > board()->track()->tileCount() - 1;
}

int MoveAction::destinationTileIndex() const
{
	int entryTileIndex{board()->entryTileIndex(player())};

	return board()->track()->distance(entryTileIndex, _srcTileIndex) + _steps;
}
