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
#include "Board.h"
#include "Path.h"

MoveAction::MoveAction(Board *board, int playerId, int srcTileIndex, int steps) :
	AbstractGameAction{board},
	_playerId{playerId},
	_srcTileIndex{srcTileIndex},
	_steps{steps}
{

}

bool MoveAction::isPossible() const
{
	return exceedsTrackLength() ? canEscape() : canMove();
}

bool MoveAction::trigger()
{
	if (!isPossible())
		return false;

	if (exceedsTrackLength())
		takePawnOut();
	else
		movePawn();

	return true;
}

bool MoveAction::canMove() const
{
	return board()->_track->canMove(_playerId, _srcTileIndex, _steps);
}

bool MoveAction::canEscape() const
{
    // TODO: Implement me
	return false;//board()->_homeAreas.at(_playerId)->canBringPawnIn();
}

void MoveAction::movePawn()
{
	board()->_track->movePawn(_playerId, _srcTileIndex, _steps);
}

void MoveAction::takePawnOut()
{
    // TODO: Implement me
}

bool MoveAction::exceedsTrackLength() const
{
	int entryTileIndex{board()->entryTileIndex(_playerId)};
	int trip{board()->_track->distance(entryTileIndex, _srcTileIndex)};

	return trip + _steps >= board()->_track->tileCount();
}
