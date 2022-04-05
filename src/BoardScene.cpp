#include "BoardScene.h"
#include "FieldItem.h"
#include "PlayerItem.h"

BoardScene::BoardScene(QObject *parent) :
	QGraphicsScene{parent},
	m_canBringPawnOn{false}
{
	const QList<int> &colors{0x2196F3, 0xFFEB3B, 0x4CAF50, 0xF44336};

	setSceneRect(0, 0, 760, 760);
//	addRect(0, 0, 760, 760);

	createPath();
	createPlayers(colors);
	createFields(colors);
}

bool BoardScene::canBringOn() const
{
return m_canBringPawnOn;
}

void BoardScene::enableBringOn(bool canBringOn)
{
	m_canBringPawnOn = canBringOn;
}

void BoardScene::createPath()
{
	addPolygon(QVector<QPointF>{
				   QPoint(310, 730), QPoint(310, 450), QPoint(30, 450),
				   QPoint(30, 310), QPoint(310, 310), QPoint(310, 30),
				   QPoint(450, 30), QPoint(450, 310), QPoint(730, 310),
				   QPoint(730, 450), QPoint(450, 450), QPoint(450, 730)
			   }, QPen(QBrush(0x313131), 4));
}

void BoardScene::createPlayers(const QList<int> &colors)
{
	for (int n = 0; n < 4; n++) {
		auto *player = new PlayerItem(colors.at(n));

		player->setPos(630*(n / 2) + 65, -630*(n / 2 != n % 2) + 695);

		addItem(player);

		m_playerItems.append(player);
	}
}

void BoardScene::createFields(const QList<int> &colors)
{
	const QList<int> &directions{2, 3, 2, 1, 2, 1, 0, 1, 0, 3, 0, 3};

	int x = 310;
	int y = 730;
	int k = -1;

	for (int n = 0; n < 40; n++) {
		auto *field{new FieldItem()};
		int mod10 = n % 10;

		field->setNumber(n);
		field->setPos(x, y);

		if (!mod10)
			field->setColor(colors.at(n / 10));

		addItem(field);

		m_fieldItems.append(field);

		if (!(mod10 % 4))
			k++;

		int direction = directions.at(k);

		x = direction == 1 ? x + 70 : direction == 3 ? x - 70 : x;
		y = direction == 0 ? y + 70 : direction == 2 ? y - 70 : y;
	}
}
