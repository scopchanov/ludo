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
#include <QJsonArray>
#include <QJsonObject>

#define PLAYER_OFFSET 10
#define PLAYERS_COUNT 4
#define PAWNS_PRO_PLAYER 4

Board::Board(QObject *parent) :
	QObject{parent},
	_track{new Path(PLAYERS_COUNT*PLAYER_OFFSET, this)}
{
	for (int n{0}; n < PLAYERS_COUNT; n++) {
		_homeAreas.append(new Path(PAWNS_PRO_PLAYER, this));
		_baseAreas.append(new Base(this));
	}

	connect(_track, &Path::pawnBusted, this, &Board::onPawnBusted);
}

QJsonObject Board::state() const
{
	QJsonArray baseAreas;
	QJsonArray homeAreas;
	QJsonArray track;

	for (size_t m{0}; m < PLAYERS_COUNT; m++) {
		auto *baseArea{_baseAreas.at(m)};
		auto *homeArea{_homeAreas.at(m)};
		QJsonArray home;

		for (int tileIndex{0}; tileIndex < homeArea->tileCount(); tileIndex++) {
			Player player{homeArea->playerAt(tileIndex)};

			if (player.has_value())
				home.append(QJsonObject{{"index", tileIndex},
										{"player", player.value()}});
		}

		baseAreas.append(baseArea->pawnCount());
		homeAreas.append(home);
	}

	for (int tileIndex{0}; tileIndex < _track->tileCount(); tileIndex++) {
		Player player{_track->playerAt(tileIndex)};

		if (player.has_value())
			track.append(QJsonObject{{"index", tileIndex},
									 {"player", player.value()}});
	}

	return QJsonObject{{"baseAreas", baseAreas},
					   {"homeAreas", homeAreas},
					   {"track", track}};
}

void Board::setState(const QJsonObject &json)
{
	const QJsonArray &baseAreas{json.value("baseAreas").toArray()};
	const QJsonArray &homeAreas{json.value("homeAreas").toArray()};
	const QJsonArray &track{json.value("track").toArray()};

	for (int n{}; n < baseAreas.count(); n++)
		_baseAreas.at(n)->setPawnCount(baseAreas.at(n).toInt());

	for (int n{0}; n < homeAreas.count(); n++) {
		const QJsonArray &homeAreaSettings{homeAreas.at(n).toArray()};

		for (const auto &tileSettings : homeAreaSettings)
			setPathTileState(_homeAreas.at(n), tileSettings.toObject());
	}

	for (const auto &tileSettings : track)
		setPathTileState(_track, tileSettings.toObject());
}

Path *Board::track() const
{
	return _track;
}

bool Board::canBringIn(int player) const
{
	auto *baseArea{_baseAreas.at(player)};

	if (baseArea->isEmpty())
		return false;

	return _track->canBringPawnIn(player, entryTileIndex(player));
}

QList<int> Board::findPossibleMoves(int player, int score)
{
	QList<int> moves;

	for (int tileIndex{0}; tileIndex < _track->tileCount(); tileIndex++)
		if (MoveAction(this, player, tileIndex, score).isPossible())
			moves.append(tileIndex);

	return moves;
}

bool Board::bringPawnIn(int player)
{
	if (!canBringIn(player))
		return false;

	_baseAreas.at(player)->removePawn();

	return _track->bringPawnIn(player, entryTileIndex(player));
}

bool Board::movePawn(int player, int srcTileIndex, int steps)
{
	return _track->movePawn(player, srcTileIndex, steps);
}

bool Board::takePawnOut(int tileIndex, int score)
{
	// auto *pawn{_track->takePawn(tileIndex)};

	// if (!pawn)
	// 	return false;

	// auto *home{_homeAreas.at(pawn->player())};

	// if (!home->bringPawnIn(pawn, wrappedIndex(pawn->trip() + score)))
	// 	return false;

	// if (home->isFull())
	// 	emit playerEscaped(pawn->player());

	// return true;

	return false;
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

void Board::setPathTileState(Path *path, const QJsonObject &json)
{
	int player{json.value("player").toInt()};
	int index{json.value("index").toInt()};

	path->setPlayerAt(player, index);
}

int Board::entryTileIndex(int player) const
{
	return player*PLAYER_OFFSET;
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

void Board::onPawnBusted(int player)
{
	_baseAreas.at(player)->addPawn();
}
