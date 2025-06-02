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

#include "GameSerializer.h"
#include "../Game.h"
#include "../Game_p.h"
#include "../Dice.h"
#include "../Base.h"
#include "../Board.h"
#include "../Path.h"
#include <QJsonArray>

GameSerializer::GameSerializer(GamePrivate *game_p) :
	_game_p{game_p}
{

}

QJsonObject GameSerializer::serialize() const
{
	return QJsonObject{{"currentPlayer", _game_p->currentplayer},
					   {"score", _game_p->dice->score()},
					   {"board", serializeBoard()},
					   {"winners", serializeWinners()}};
}

void GameSerializer::deserialize(const QJsonObject &json)
{
	_game_p->currentplayer = json.value("currentPlayer").toInt();
	_game_p->dice->setScore(json.value("score").toInt());

	deserializeBoard(json.value("board").toObject());
	deserializeWinners(json.value("winners").toArray());
}

QJsonObject GameSerializer::serializeBoard() const
{
	return QJsonObject{{"baseAreas", serializeBaseAreas()},
					   {"homeAreas", serializeHomeAreas()},
					   {"track", serializePath(_game_p->board->track())}};
}

QJsonArray GameSerializer::serializeWinners() const
{
	QJsonArray winners;

	for (const auto &winner : std::as_const(_game_p->winners))
		winners.append(winner);

	return winners;
}

QJsonArray GameSerializer::serializeBaseAreas() const
{
	QJsonArray baseAreas;

	for (int n{0}; n < _game_p->playerCount; n++)
		baseAreas.append(_game_p->board->baseArea(n)->pawnCount());

	return baseAreas;
}

QJsonArray GameSerializer::serializeHomeAreas() const
{
	QJsonArray homeAreas;

	for (int n{0}; n < _game_p->playerCount; n++)
		homeAreas.append(serializePath(_game_p->board->homeArea(n)));

	return homeAreas;
}

QJsonArray GameSerializer::serializePath(Path *path) const
{
	QJsonArray pawns;

	for (int n{0}; n < path->tileCount(); n++) {
		Player player{path->playerAt(n)};

		if (player.has_value())
			pawns.append(QJsonObject{{"index", n},
									 {"player", player.value()}});
	}

	return pawns;
}

void GameSerializer::deserializeBoard(const QJsonObject &json)
{
	deserializeBaseAreas(json.value("baseAreas").toArray());
	deserializeHomeAreas(json.value("homeAreas").toArray());
	deserializePath(_game_p->board->track(), json.value("track").toArray());
}

void GameSerializer::deserializeWinners(const QJsonArray &winners)
{
	for (auto winner : winners)
		_game_p->winners.append(winner.toInt());
}

void GameSerializer::deserializeBaseAreas(const QJsonArray &baseAreas)
{
	for (int n{0}; n < baseAreas.count(); n++)
		_game_p->board->baseArea(n)->setPawnCount(baseAreas.at(n).toInt());
}

void GameSerializer::deserializeHomeAreas(const QJsonArray &homeAreas)
{
	for (int n{0}; n < homeAreas.count(); n++)
		deserializePath(_game_p->board->homeArea(n), homeAreas.at(n).toArray());
}

void GameSerializer::deserializePath(Path *path, const QJsonArray &pawns)
{
	for (const auto &value : pawns) {
		const auto &pawn{value.toObject()};
		int player{pawn.value("player").toInt()};
		int index{pawn.value("index").toInt()};

		path->setPlayerAt(player, index);
	}
}
