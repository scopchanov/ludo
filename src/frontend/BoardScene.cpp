#include "BoardScene.h"
#include "FieldItem.h"
#include "SpawnItem.h"
#include "ArrowItem.h"
#include "HomeItem.h"

BoardScene::BoardScene(QObject *parent) :
	QGraphicsScene{parent},
	m_currentPlayerId{0},
	m_canBringPawnOn{false}
{
	setSceneRect(0, 0, 760, 760);
//	addRect(0, 0, 760, 760);

	createPath();
	createPlayers();
	createFields();

	auto *home = new HomeItem(m_playerItems.at(0)->color());

	home->setPos(380, 555);
	home->setRotation(0);

	addItem(home);

	home = new HomeItem(m_playerItems.at(1)->color());

	home->setPos(205, 380);
	home->setRotation(90);

	addItem(home);

	home = new HomeItem(m_playerItems.at(2)->color());

	home->setPos(380, 205);
	home->setRotation(180);

	addItem(home);

	home = new HomeItem(m_playerItems.at(3)->color());

	home->setPos(555, 380);
	home->setRotation(270);

	addItem(home);
}

bool BoardScene::canBringOn() const
{
	return m_canBringPawnOn;
}

int BoardScene::currentPlayerId() const
{
	return m_currentPlayerId;
}

void BoardScene::setCurrentPlayerId(int currentPlayerId)
{
	m_currentPlayerId = currentPlayerId;
}

void BoardScene::clearHighlight()
{
	for (auto *field : qAsConst(m_fieldItems))
		field->setHighlighted(false);
}

void BoardScene::updateBoard(const QList<QPair<int, int> > &pawns)
{
	for (auto *field : qAsConst(m_fieldItems))
		field->setPawnColor(QColor());

	for (const auto &pawn : pawns)
		m_fieldItems.at(pawn.first)->setPawnColor(m_playerItems.at(pawn.second)->color());
}

void BoardScene::enableBringOn(bool canBringOn)
{
	m_canBringPawnOn = canBringOn;

	for (auto *arrow : qAsConst(m_arrowItems))
		arrow->setHighlighted(m_canBringPawnOn
							  && arrow->number() == m_currentPlayerId);
}

void BoardScene::highlightFields(const QList<int> &moves)
{
	for (const auto &move : moves)
		m_fieldItems.at(move)->setHighlighted(true);
}

void BoardScene::changePawnCount(int playerId, int pawnCount)
{
	m_playerItems.at(playerId)->setPawnCount(pawnCount);
}

void BoardScene::createPath()
{
	addPolygon(QVector<QPointF>{
				   QPoint(310, 730), QPoint(310, 450), QPoint(30, 450),
				   QPoint(30, 310), QPoint(310, 310), QPoint(310, 30),
				   QPoint(450, 30), QPoint(450, 310), QPoint(730, 310),
				   QPoint(730, 450), QPoint(450, 450), QPoint(450, 730)
			   }, QPen(QBrush(0x424242), 4));
}

void BoardScene::createPlayers()
{
	for (int n = 0; n < 4; n++) {
		auto *player = new SpawnItem(n);

		player->setPos(630*(n / 2) + 65, -630*(n / 2 != n % 2) + 695);

		addItem(player);

		m_playerItems.append(player);

		auto *arrow = new ArrowItem();

		arrow->setNumber(n);
		arrow->setColor(player->color());
		arrow->setRotation(90*n);

		switch (n) {
		case 0:
			arrow->setPos(205, 730);
			break;
		case 1:
			arrow->setPos(30, 205);
			break;
		case 2:
			arrow->setPos(555, 30);
			break;
		case 3:
			arrow->setPos(730, 555);
			break;
		}

		addItem(arrow);

		m_arrowItems.append(arrow);
	}
}

void BoardScene::createFields()
{
	const QList<int> &directions{2, 3, 2, 1, 2, 1, 0, 1, 0, 3, 0, 3};
	int x = 310;
	int y = 730;
	int k = -1;

	for (int n = 0; n < 40; n++) {
		auto *field = new FieldItem();
		int mod10 = n % 10;

		field->setNumber(n);
		field->setPos(x, y);

		if (!mod10)
			field->setColor(m_playerItems.at(n / 10)->color());

		addItem(field);

		m_fieldItems.append(field);

		if (!(mod10 % 4))
			k++;

		int direction = directions.at(k);

		x = direction == 1 ? x + 70 : direction == 3 ? x - 70 : x;
		y = direction == 0 ? y + 70 : direction == 2 ? y - 70 : y;
	}
}
