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

#include "BoardScene.h"
#include "DiceItem.h"
#include "TileItem.h"
#include "BaseItem.h"
#include "ArrowItem.h"
#include "HomeItem.h"
#include "PlayerItem.h"
#include <QJsonObject>
#include <QJsonArray>

BoardScene::BoardScene(QObject *parent) :
	QGraphicsScene{parent},
	_diceItem{new DiceItem()}
{
	setSceneRect(-50, -50, 860, 860);

	createPath();
	createBaseAreas();
	createHomeAreas();
    createTiles();
	createPlayers();

	_diceItem->setPos(380, 380);

	addItem(_diceItem);
}

void BoardScene::highlightPlayer(int playerId)
{
	_playerItems.at(playerId)->clearText();

	for (auto *player : std::as_const(_playerItems))
		player->setHighlighted(player->number() == playerId);
}

void BoardScene::setPlayerText(int playerId, const QString &str)
{
	_playerItems.at(playerId)->setText(str);
}

void BoardScene::setScore(int value)
{
	_diceItem->setScore(value);
}

void BoardScene::clearHighlight()
{
	for (auto *tile : std::as_const(_tileItems))
		tile->setHighlighted(false);
}

void BoardScene::clearPlayersText()
{
	for (auto *player : std::as_const(_playerItems))
		player->clearText();
}

void BoardScene::updateBoard(const QJsonObject &json)
{
	for (auto *tile : std::as_const(_tileItems))
		tile->setPawnColor(QColor());

	const QJsonArray &track{json.value("track").toArray()};
	const QJsonArray &homeAreas{json.value("homeAreas").toArray()};
	QList<int> k{0, 0, 0, 0};

	for (const auto &value : track) {
		const QJsonObject &jsonTile{value.toObject()};
		int index{jsonTile.value("index").toInt()};
		int playerId{jsonTile.value("player").toInt()};

		_tileItems.at(index)->setPawnColor(_baseItems.at(playerId)->color());
		k[playerId]++;
	}

	for (int n{0}; n < _homeItems.count(); n++)
		_homeItems.at(n)->updateItem(homeAreas.at(n).toArray());

	for (int n{0}; n < k.count(); n++)
		_baseItems.at(n)->setPawnCount(4 - k.at(n));
}

void BoardScene::updateArrows(bool canBringIn)
{
	for (auto *arrow : std::as_const(_arrowItems))
		arrow->setVisible(canBringIn && isCurrentArrow(arrow));
}

void BoardScene::showMoves(const QList<int> &moves)
{
	for (const auto &move : moves)
		_tileItems.at(move)->setHighlighted(true);
}

void BoardScene::createPath()
{
	addPolygon(QList<QPointF>{
				   QPoint(310, 730), QPoint(310, 450), QPoint(30, 450),
				   QPoint(30, 310), QPoint(310, 310), QPoint(310, 30),
				   QPoint(450, 30), QPoint(450, 310), QPoint(730, 310),
				   QPoint(730, 450), QPoint(450, 450), QPoint(450, 730)
			   }, QPen(QBrush(0x424242), 4));
}

void BoardScene::createBaseAreas()
{
	for (int n{0}; n < 4; n++) {
		auto *island{new BaseItem(n, playerColor(n))};

		island->setPos(630*(n / 2) + 65, -630*(n / 2 != n % 2) + 695);
		island->setRotation(90*n);

		addItem(island);

		_baseItems.append(island);

		auto *arrow{new ArrowItem()};

		arrow->setColor(island->color());
		arrow->setRotation(90*n);
		arrow->setVisible(false);

		switch (n) {
		case 0:
			arrow->setPos(235, 730);
			break;
		case 1:
			arrow->setPos(30, 235);
			break;
		case 2:
			arrow->setPos(525, 30);
			break;
		case 3:
			arrow->setPos(730, 525);
			break;
		}

		addItem(arrow);

		_arrowItems.append(arrow);
	}
}

void BoardScene::createHomeAreas()
{
	for (int n{0}; n < 4; n++) {
		auto *home{new HomeItem(_baseItems.at(n)->color())};
		double pi{3.1415};

		home->setPos(175*round(sin((4 - n)*pi/2)) + 380,
					 175*round(cos((4 - n)*pi/2)) + 380);
		home->setRotation(90*n);

		addItem(home);

		_homeItems.append(home);
	}
}

void BoardScene::createTiles()
{
	const QList<int> &directions{2, 3, 2, 1, 2, 1, 0, 1, 0, 3, 0, 3};
	int x{310};
	int y{730};
	int k{-1};

	for (int n{0}; n < 40; n++) {
		auto *field{new TileItem()};
		int mod10{n % 10};

		field->setNumber(n);
		field->setPos(x, y);

		if (!mod10)
			field->setColor(_baseItems.at(n / 10)->color());

		addItem(field);

		_tileItems.append(field);

		if (!(mod10 % 4))
			k++;

		int direction{directions.at(k)};

		x = direction == 1 ? x + 70 : direction == 3 ? x - 70 : x;
		y = direction == 0 ? y + 70 : direction == 2 ? y - 70 : y;
	}
}

void BoardScene::createPlayers()
{
	for (int n{0}; n < 4; n++) {
		auto *player{new PlayerItem()};

		player->setNumber(n);
		player->setColor(playerColor(n));

		if (!n)
			player->setHighlighted(true);

		addItem(player);
		_playerItems.append(player);

		switch (n) {
		case 0:
			player->setPos(205, 555);
			break;
		case 1:
			player->setPos(205, 205);
			break;
		case 2:
			player->setPos(555, 205);
			break;
		case 3:
			player->setPos(555, 555);
			break;
		}
	}
}

int BoardScene::playerColor(int playerId) const
{
	return QList<int>{0x1976D2, 0xFBC02D, 0x388E3C, 0xD32F2F}.at(playerId);
}

bool BoardScene::isCurrentArrow(ArrowItem *arrow) const
{
	for (auto *player : _playerItems)
		if (player->isHighlighted() && haveSameIndex(player, arrow))
			return true;

	return false;
}

bool BoardScene::haveSameIndex(PlayerItem *player, ArrowItem *arrow) const
{
	return _playerItems.indexOf(player) == _arrowItems.indexOf(arrow);
}
