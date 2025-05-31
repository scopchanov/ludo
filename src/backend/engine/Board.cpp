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

#include "Board.h"
#include "Base.h"
#include "Path.h"
#include "actions/MoveAction.h"

#define PLAYER_OFFSET 10
#define PLAYER_COUNT 4
#define PAWNS_PRO_PLAYER 4

Board::Board(QObject *parent) :
	QObject{parent},
	_track{new Path(PLAYER_COUNT*PLAYER_OFFSET, this)}
{
	for (int n{0}; n < PLAYER_COUNT; n++) {
		auto *homeArea{new Path(PAWNS_PRO_PLAYER, this)};

		_baseAreas.append(new Base(this));
		_homeAreas.append(homeArea);

		connect(homeArea, &Path::pathFull, this, &Board::onHomeFull);
	}

	connect(_track, &Path::pawnBusted, this, &Board::onPawnBusted);
}

Base *Board::baseArea(int player) const
{
	return isValidPlayer(player) ? _baseAreas.at(player) : nullptr;
}

Path *Board::homeArea(int player) const
{
	return isValidPlayer(player) ? _homeAreas.at(player) : nullptr;
}

Path *Board::track() const
{
	return _track;
}

int Board::entryTileIndex(int player) const
{
	return player*PLAYER_OFFSET;
}

void Board::init()
{
	for (auto &baseArea : std::as_const(_baseAreas))
		baseArea->setPawnCount(PAWNS_PRO_PLAYER);
}

void Board::clear()
{
	_track->clear();

	for (auto *base : std::as_const(_baseAreas))
		base->clear();

	for (auto *home : std::as_const(_homeAreas))
		home->clear();
}

bool Board::isValidPlayer(int player) const
{
	return player >= 0 && player < PLAYER_COUNT;
}

void Board::onPawnBusted(int player)
{
	_baseAreas.at(player)->addPawn();
}

void Board::onHomeFull()
{
	emit playerEscaped(_homeAreas.indexOf(sender()));
}
