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

#include "BoardSerializer.h"
#include "../Base.h"
#include "../Board.h"
#include "../Path.h"
#include <QJsonArray>

#define PLAYERS_COUNT 4

BoardSerializer::BoardSerializer()
{

}

QJsonObject BoardSerializer::toJson(Board *board)
{
	QJsonArray baseAreas;
	QJsonArray homeAreas;
	QJsonArray track;

	for (int player{0}; player < PLAYERS_COUNT; player++) {
		auto *baseArea{board->baseArea(player)};
		auto *homeArea{board->homeArea(player)};
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

	for (int tileIndex{0}; tileIndex < board->track()->tileCount(); tileIndex++) {
		Player player{board->track()->playerAt(tileIndex)};

		if (player.has_value())
			track.append(QJsonObject{{"index", tileIndex},
									 {"player", player.value()}});
	}

	return QJsonObject{{"baseAreas", baseAreas},
					   {"homeAreas", homeAreas},
					   {"track", track}};
}

void BoardSerializer::fromJson(Board *board, const QJsonObject &json)
{
	const QJsonArray &baseAreas{json.value("baseAreas").toArray()};
	const QJsonArray &homeAreas{json.value("homeAreas").toArray()};
	const QJsonArray &track{json.value("track").toArray()};

	for (int n{}; n < baseAreas.count(); n++)
		board->baseArea(n)->setPawnCount(baseAreas.at(n).toInt());

	for (int n{0}; n < homeAreas.count(); n++) {
		const QJsonArray &homeAreaSettings{homeAreas.at(n).toArray()};

		for (const auto &tileSettings : homeAreaSettings)
			setPathTileState(board->homeArea(n), tileSettings.toObject());
	}

	for (const auto &tileSettings : track)
		setPathTileState(board->track(), tileSettings.toObject());
}


void BoardSerializer::setPathTileState(Path *path, const QJsonObject &json)
{
	int player{json.value("player").toInt()};
	int index{json.value("index").toInt()};

	path->setPlayerAt(player, index);
}
