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
	setSceneRect(-450, -450, 900, 900);

	for (int n{0}; n < 4; n++) {
		createBaseArea(n);
		createHomeArea(n);
		createPlayer(n);
		createArrow(n);
	}

	createPath();
	createTiles();

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
	const QJsonArray &baseAreas{json.value("baseAreas").toArray()};
	const QJsonArray &homeAreas{json.value("homeAreas").toArray()};
	const QJsonArray &track{json.value("track").toArray()};

	for (auto *tile : std::as_const(_tileItems))
		tile->setPawnColor(QColor());

	for (const auto &value : track) {
		const QJsonObject &jsonTile{value.toObject()};
		int index{jsonTile.value("index").toInt()};
		int playerId{jsonTile.value("player").toInt()};

		_tileItems.at(index)->setPawnColor(_baseItems.at(playerId)->color());
	}

	for (int n{0}; n < _homeItems.count(); n++)
		_homeItems.at(n)->updateItem(homeAreas.at(n).toArray());

	for (int n{0}; n < _baseItems.count(); n++)
		_baseItems.at(n)->setPawnCount(baseAreas.at(n).toInt());
}

void BoardScene::updateWinners(const QJsonArray &winners)
{
	for (int n{0}; n < winners.count(); n++)
		_playerItems.at(winners.at(n).toInt())->setPlace(n + 1);
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

void BoardScene::createBaseArea(int n)
{
	auto *base{new BaseItem(n, playerColor(n))};
	int distance{315};
	int x{n < 2 ? -distance : distance};
	int y{n % 3 ? -distance : distance};

	base->setPos(x, y);
	base->setRotation(90*n);

	addItem(base);

	_baseItems.append(base);
}

void BoardScene::createHomeArea(int n)
{
	auto *home{new HomeItem(_baseItems.at(n)->color())};
	double pi{3.1415};

	home->setPos(175*round(sin((4 - n)*pi/2)), 175*round(cos((4 - n)*pi/2)));
	home->setRotation(90*n);

	addItem(home);

	_homeItems.append(home);
}

void BoardScene::createPlayer(int n)
{
	auto *player{new PlayerItem()};
	int distance{175};
	int x{n < 2 ? -distance : distance};
	int y{n % 3 ? -distance : distance};

	player->setNumber(n);
	player->setColor(playerColor(n));
	player->setPos(x, y);

	addItem(player);
	_playerItems.append(player);
}

void BoardScene::createArrow(int n)
{
	auto *arrow{new ArrowItem()};

	arrow->setColor(playerColor(n));
	arrow->setRotation(90*n);
	arrow->setVisible(false);

	switch (n) {
	case 0:
		arrow->setPos(-145, 350);
		break;
	case 1:
		arrow->setPos(-350, -145);
		break;
	case 2:
		arrow->setPos(145, -350);
		break;
	case 3:
		arrow->setPos(350, 145);
		break;
	}

	addItem(arrow);

	_arrowItems.append(arrow);
}

void BoardScene::createPath()
{
	addPolygon(QList<QPointF>{
				   QPoint(-70, 350), QPoint(-70, 70), QPoint(-350, 70),
				   QPoint(-350, -70), QPoint(-70, -70), QPoint(-70, -350),
				   QPoint(70, -350), QPoint(70, -70), QPoint(350, -70),
				   QPoint(350, 70), QPoint(70, 70), QPoint(70, 350)
			   }, QPen(QBrush(0x424242), 4));
}

void BoardScene::createTiles()
{
	const QList<int> &directions{2, 3, 2, 1, 2, 1, 0, 1, 0, 3, 0, 3};
	int x{-70};
	int y{350};
	int k{-1};

	for (int n{0}; n < 40; n++) {
		auto *tile{new TileItem()};
		int mod10{n % 10};

		if (!mod10)
			tile->setColor(_baseItems.at(n / 10)->color());

		tile->setNumber(n);
		tile->setPos(x, y);

		addItem(tile);

		_tileItems.append(tile);

		if (!(mod10 % 4))
			k++;

		int direction{directions.at(k)};

		x += direction == 1 ? 70 : direction == 3 ? -70 : 0;
		y += direction == 0 ? 70 : direction == 2 ? -70 : 0;
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
