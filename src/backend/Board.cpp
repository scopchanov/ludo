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
#include <QJsonObject>
#include <QJsonArray>

#define CIRCULAR_LENGHT 40
#define HOME_LENGTH 4
#define PLAYER_OFFSET 10

Board::Board(QObject *parent) :
	QObject{parent},
	_track{new Path(CIRCULAR_LENGHT, this)}
{
	for (int n{0}; n < 4; n++)
		_homes.append(new Path(HOME_LENGTH, this));
}

QJsonObject Board::boardLayout() const
{
	QJsonObject json;
	QJsonArray pathway;
	QJsonArray homes;

	for (int n{0}; n < _track->tileCount(); n++) {
		auto *pawn{_track->pawnAt(n)};

		if (pawn)
			pathway.append(QJsonObject{{"number", n},
									   {"player", pawn->playerId()}});
	}

	json["pathway"] = pathway;

	for (size_t m{0}; m < 4; m++) {
		QJsonArray home;

		for (int n{0}; n < 4; n++) {
			auto *pawn{_homes.at(m)->pawnAt(n)};

			if (pawn)
				home.append(QJsonObject{{"number", n},
										{"player", pawn->playerId()}});
		}

		homes.append(home);
	}

	json["homes"] = homes;

	return json;
}

QList<int> Board::findPossibleMoves(int playerId, int score) const
{
	QList<int> moves;

	for (int n{0}; n < _track->tileCount(); n++) {
		auto *pawn{_track->pawnAt(n)};

		if (pawn && pawn->playerId() == playerId && canPlay(pawn, score, n))
			moves.append(n);
	}

	return moves;
}

bool Board::canBringIn(int playerId) const
{
	auto *pawn{_track->pawnAt(entryTile(playerId))};

	return !pawn || pawn->playerId() != playerId;
}

bool Board::bringPawnIn(Pawn *pawn)
{
	if (!pawn)
		return false;

	return _track->bringPawnIn(pawn, entryTile(pawn->playerId()));
}

bool Board::movePawn(int playerId, int srcTileNumber, int steps)
{
	auto *pawn{_track->pawnAt(srcTileNumber)};

	if (!pawn || pawn->playerId() != playerId)
		return false;

	if(exceedsTrackLength(pawn, steps) && canBringOut(pawn, steps))
		return takePawnOut(srcTileNumber, steps);

	if (canMove(playerId, srcTileNumber, steps))
		return _track->movePawn(srcTileNumber, steps);

	return false;
}

bool Board::takePawnOut(int tileNumber, int score)
{
	auto *pawn{_track->takePawn(tileNumber)};

	if (!pawn)
		return false;

	auto *home{_homes.at(pawn->playerId())};

	if (!home->bringPawnIn(pawn, pawn->trip() - 40 + score))
		return false;

	if (home->isFull())
		emit playerEscaped(pawn->playerId());

	return true;
}

void Board::reset()
{
	_track->reset();

	for (auto *home : std::as_const(_homes))
		home->reset();
}

bool Board::canMove(int playerId, int srcTileNumber, int steps) const
{
	auto *pawn{_track->pawnAt(wrappedIndex(srcTileNumber + steps))};

	return !pawn || pawn->playerId() != playerId;
}

bool Board::canBringOut(Pawn *pawn, int score) const
{
	if (!pawn)
		return false;

	int fieldNum{pawn->trip() + score - _track->tileCount()};

	if (fieldNum > 3)
		return false;

	return !_homes.at(pawn->playerId())->pawnAt(fieldNum);
}

int Board::entryTile(int playerId) const
{
	return playerId*PLAYER_OFFSET;
}

int Board::wrappedIndex(int index) const
{
	return index % _track->tileCount();
}

bool Board::exceedsTrackLength(Pawn *pawn, int steps) const
{
	return pawn->trip() + steps > _track->tileCount();
}

bool Board::canPlay(Pawn *pawn, int steps, int tileNumber) const
{
	return exceedsTrackLength(pawn, steps)
			? canBringOut(pawn, steps)
			: canMove(pawn->playerId(), tileNumber, steps);
}
