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
#include "Path.h"
#include "Tile.h"
#include "Pawn.h"
#include "Move.h"
#include <QJsonObject>
#include <QJsonArray>

#define TRACK_LENGHT 40
#define HOME_LENGTH 4
#define PLAYER_OFFSET 10

Board::Board(QObject *parent) :
	QObject{parent},
	_track{new Path(TRACK_LENGHT, this)}
{
	for (int n{0}; n < 4; n++)
		_homeAreas.append(new Path(HOME_LENGTH, this));
}

QJsonObject Board::boardLayout() const
{
	QJsonObject json;
	QJsonArray track;
	QJsonArray homes;

	for (int n{0}; n < _track->tileCount(); n++) {
		auto *pawn{_track->pawnAt(n)};

		if (pawn)
			track.append(QJsonObject{{"index", n},
									 {"player", pawn->playerId()}});
	}

	json["track"] = track;

	for (size_t m{0}; m < 4; m++) {
		QJsonArray home;

		for (int n{0}; n < 4; n++) {
			auto *pawn{_homeAreas.at(m)->pawnAt(n)};

			if (pawn)
				home.append(QJsonObject{{"index", n},
										{"player", pawn->playerId()}});
		}

		homes.append(home);
	}

	json["homes"] = homes;

	return json;
}

bool Board::canBringIn(Pawn *pawn) const
{
	if (!pawn)
		return false;

	return pawn->canOccupy(_track->tile(entryTileIndex(pawn->playerId())));
}

QList<int> Board::findPossibleMoves(int playerId, int score)
{
	QList<int> moves;

	for (int n{0}; n < _track->tileCount(); n++) {
		auto *pawn{_track->pawnAt(n)};

		if (pawn && pawn->playerId() == playerId
			&& Move(pawn, score, this).isPossible())
			moves.append(n);
	}

	return moves;
}

bool Board::bringPawnIn(Pawn *pawn)
{
	if (!pawn)
		return false;

	return _track->bringPawnIn(pawn, entryTileIndex(pawn->playerId()));
}

bool Board::movePawn(int playerId, int srcTileNumber, int steps)
{
	auto *pawn{_track->pawnAt(srcTileNumber)};

	if (!pawn || pawn->playerId() != playerId)
		return false;

	return Move(pawn, steps, this).make();
}

bool Board::takePawnOut(int tileIndex, int score)
{
	// auto *pawn{_track->takePawn(tileIndex)};

	// if (!pawn)
	// 	return false;

	// auto *home{_homeAreas.at(pawn->playerId())};

	// if (!home->bringPawnIn(pawn, wrappedIndex(pawn->trip() + score)))
	// 	return false;

	// if (home->isFull())
	// 	emit playerEscaped(pawn->playerId());

	// return true;

	return false;
}

void Board::reset()
{
	_track->reset();

	for (auto *home : std::as_const(_homeAreas))
		home->reset();
}

bool Board::canMove(int playerId, int srcTileNumber, int steps) const
{
	// auto *pawn{_track->pawnAt(wrappedIndex(srcTileNumber + steps))};

	// return !pawn || pawn->playerId() != playerId;

	return false;
}

bool Board::canBringOut(Pawn *pawn, int score) const
{
	// if (!pawn)
	// 	return false;

	// int fieldNum{pawn->trip() + score - _track->tileCount()};

	// if (fieldNum > 3)
	// 	return false;

	// return !_homeAreas.at(pawn->playerId())->pawnAt(fieldNum);

	return false;
}

// bool Board::canPlay(Pawn *pawn, int steps) const
// {
// 	return pawn->canOccupy(exceedsTrackLength(pawn, steps)
// 							   ? homeTile(pawn, steps)
// 							   : trackTile(pawn, steps));
// }

// bool Board::exceedsTrackLength(Pawn *pawn, int steps) const
// {
// 	return pawn->trip() + steps > _track->tileCount();
// }

// Tile *Board::trackTile(Pawn *pawn, int steps) const
// {
// 	int playerId{pawn->playerId()};
// 	int tileIndex{wrappedIndex(entryTile(playerId) + pawn->trip() + steps)};

// 	return _track->tile(tileIndex);
// }

// Tile *Board::homeTile(Pawn *pawn, int steps) const
// {
// 	int tileIndex{wrappedIndex(pawn->trip() + steps)};

// 	return _homeAreas.at(pawn->playerId())->tile(tileIndex);
// }

int Board::entryTileIndex(int playerId) const
{
	return playerId*PLAYER_OFFSET;
}

// int Board::wrappedIndex(int index) const
// {
// 	return index % _track->tileCount();
// }
