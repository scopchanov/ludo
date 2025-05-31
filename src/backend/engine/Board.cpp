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
#include "MoveAction.h"
#include "Path.h"
#include "Pawn.h"
#include <QJsonArray>
#include <QJsonObject>

#define TRACK_LENGHT 40
#define HOME_LENGTH 4
#define PLAYER_OFFSET 10
#define PLAYERS_COUNT 4
#define PAWNS_PRO_PLAYER 4

Board::Board(QObject *parent) :
	QObject{parent},
	_track{new Path(TRACK_LENGHT, this)}
{
	for (int n{0}; n < PLAYERS_COUNT; n++) {
		_pawns.append({PAWNS_PRO_PLAYER, new Pawn(n, this)});
		_homeAreas.append(new Path(HOME_LENGTH, this));
		_baseAreas.append(new Base(this));

        for (auto *pawn : _pawns.at(n))
            connect(pawn, &Pawn::gotReset, this, &Board::onPawnReset);
	}

    connect(_track, &Path::pawnBusted, this, &Board::onPawnBusted);
}

QJsonObject Board::state() const
{
	QJsonArray track;
	QJsonArray homeAreas;

	for (int n{0}; n < _track->tileCount(); n++) {
		auto *pawn{_track->pawnAt(n)};

		if (pawn)
			track.append(QJsonObject{{"index", n},
									 {"player", pawn->playerId()}});
	}

	for (size_t m{0}; m < 4; m++) {
		QJsonArray home;

		for (int n{0}; n < 4; n++) {
			auto *pawn{_homeAreas.at(m)->pawnAt(n)};

			if (pawn)
				home.append(QJsonObject{{"index", n},
										{"player", pawn->playerId()}});
		}

		homeAreas.append(home);
	}

	return QJsonObject{{"track", track}, {"homeAreas", homeAreas}};
}

void Board::setState(const QJsonObject &json)
{
	const QJsonArray &track{json.value("track").toArray()};

	for (const auto &value : track) {
		const QJsonObject &tileSettings{value.toObject()};
		int playerId{tileSettings.value("player").toInt()};
		int index{tileSettings.value("index").toInt()};
		auto *pawn{_pawns[playerId].takeLast()};

		_track->putPawnBackAt(pawn, index);
	}

	for (auto &playerPawns : _pawns)
		while (!playerPawns.isEmpty())
			_baseAreas.at(_pawns.indexOf(playerPawns))->addPawn(playerPawns.takeLast());
}

Path *Board::track() const
{
	return _track;
}

bool Board::canBringIn(int playerId) const
{
	auto *pawn{_baseAreas.at(playerId)->pawn()};

	return _track->canBringPawnIn(pawn, entryTileIndex(playerId));
}

QList<int> Board::findPossibleMoves(int playerId, int score)
{
	QList<int> moves;

	for (int tileIndex{0}; tileIndex < _track->tileCount(); tileIndex++)
		if (MoveAction(this, playerId, tileIndex, score).isPossible())
			moves.append(tileIndex);

	return moves;
}

bool Board::bringPawnIn(int playerId)
{
	auto *pawn{_baseAreas.at(playerId)->takePawn()};

	if (!pawn)
		return false;

	return _track->bringPawnIn(pawn, entryTileIndex(pawn->playerId()));
}

bool Board::movePawn(int playerId, int srcTileIndex, int steps)
{
	return _track->movePawn(playerId, srcTileIndex, steps);
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

void Board::init()
{
	for (auto &playerPawns : _pawns)
		for (auto *pawn : playerPawns)
			_baseAreas.at(pawn->playerId())->addPawn(pawn);
}

void Board::reset()
{
	_track->reset();

	for (auto *base : std::as_const(_baseAreas))
		base->reset();

	for (auto *home : std::as_const(_homeAreas))
		home->reset();
}

int Board::entryTileIndex(int playerId) const
{
	return playerId*PLAYER_OFFSET;
}

QList<QJsonObject> Board::toObjects(const QJsonArray& array)
{
	QList<QJsonObject> jsonObjects;

	jsonObjects.reserve(array.size());

	for (const QJsonValue& value : array)
		if (value.isObject())
			jsonObjects.append(value.toObject());

	return jsonObjects;
}

void Board::onPawnReset()
{
	auto *pawn{static_cast<Pawn *>(sender())};

	_pawns[pawn->playerId()].append(pawn);
}

void Board::onPawnBusted(Pawn *pawn)
{
	_baseAreas.at(pawn->playerId())->addPawn(pawn);
}
