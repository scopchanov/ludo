#include "BoardView.h"
#include "FieldItem.h"
#include <QDebug>

BoardView::BoardView(QWidget *parent) :
	QGraphicsView{parent}
{
	setBackgroundBrush(QBrush(0xFFE0B2));
	setFrameStyle(QFrame::NoFrame);
	setAlignment(Qt::AlignCenter);
	setScene(new QGraphicsScene(this));
	setSceneRect(0, 0, 760, 760);
//	scene()->addRect(0, 0, 760, 760);
	scene()->addPolygon(QVector<QPointF>{QPoint(310, 730),
										 QPoint(310, 450),
										 QPoint(30, 450),
										 QPoint(30, 310),
										 QPoint(310, 310),
										 QPoint(310, 30),
										 QPoint(450, 30),
										 QPoint(450, 310),
										 QPoint(730, 310),
										 QPoint(730, 450),
										 QPoint(450, 450),
										 QPoint(450, 730)
						}, QPen(QBrush(0x313131), 3));

	const QList<int> &directions{2, 3, 2, 1, 2, 1, 0, 1, 0, 3, 0, 3};
	const QList<int> &colors{0x2196F3, 0xFFEB3B, 0x4CAF50, 0xF44336};
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

		scene()->addItem(field);

		if (!(mod10 % 4))
			k++;

		int direction = directions.at(k);

		x = direction == 1 ? x + 70 : direction == 3 ? x - 70 : x;
		y = direction == 0 ? y + 70 : direction == 2 ? y - 70 : y;
	}
}

void BoardView::enableBringOn(bool b)
{
	qDebug() << b;

	emit bringOn();
}
