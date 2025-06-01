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

#include "BringInAction.h"
#include "../Board.h"
#include "../Base.h"
#include "../Path.h"

BringInAction::BringInAction(Board *board, int player, int score) :
	AbstractGameAction{board, player},
	_score{score}
{

}

bool BringInAction::isPossible() const
{
	return _score == 6 && hasPawnsLeft() ? canBringPawnOnTrack() : false;
}

bool BringInAction::trigger()
{
	if (!isPossible())
		return false;

	auto *track{board()->track()};

	board()->baseArea(player())->removePawn();

	return track->bringPawnIn(player(), board()->entryTileIndex(player()));
}

bool BringInAction::hasPawnsLeft() const
{
	return !board()->baseArea(player())->isEmpty();
}

bool BringInAction::canBringPawnOnTrack() const
{
	auto *track{board()->track()};

	return track->canBringPawnIn(player(), board()->entryTileIndex(player()));
}
