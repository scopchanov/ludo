#include "BoardScene.h"
#include "FieldItem.h"
#include "PlayerItem.h"
#include "qdebug.h"

BoardScene::BoardScene(QObject *parent) :
	QGraphicsScene{parent},
	m_canBringPawnOn{false}
{
	setSceneRect(0, 0, 760, 760);
//	addRect(0, 0, 760, 760);

	createPath();
	createPlayers();
	createFields();
}

bool BoardScene::canBringOn() const
{
	return m_canBringPawnOn;
}

void BoardScene::clearHighlight()
{
	for (auto *field : qAsConst(m_fieldItems))
		field->setSelected(false);
}

void BoardScene::foo(const QList<QPair<int, int> > &pawns)
{
	for (auto *field : qAsConst(m_fieldItems))
		field->setOccupationColor(QColor());

	for (const auto &pawn : pawns)
		m_fieldItems.at(pawn.first)->setOccupationColor(m_playerItems.first()->playerColor(pawn.second));


	//		qDebug() << pawn.first << pawn.second;
//		ui->listBoard->addItem(QString::number(pawn.first) + ": "
//							   + QString::number(pawn.second));
}

void BoardScene::enableBringOn(bool canBringOn)
{
	m_canBringPawnOn = canBringOn;
}

void BoardScene::highlightFields(const QList<int> &moves)
{
	for (const auto &move : moves)
		m_fieldItems.at(move)->setSelected(true);
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
		auto *player = new PlayerItem(n);

		player->setPos(630*(n / 2) + 65, -630*(n / 2 != n % 2) + 695);

		addItem(player);

		m_playerItems.append(player);
	}
}

void BoardScene::createFields()
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
