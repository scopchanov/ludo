#include "BoardView.h"
#include "BoardScene.h"
#include <QMouseEvent>
#include <QDebug>

BoardView::BoardView(QWidget *parent) :
	QGraphicsView{parent},
	m_board(new BoardScene(this))
{
	setBackgroundBrush(QBrush(0xFFE0B2));
	setFrameStyle(QFrame::NoFrame);
	setAlignment(Qt::AlignCenter);
	setScene(m_board);
}

void BoardView::enableBringOn(bool canBringOn)
{
	m_board->enableBringOn(canBringOn);
}

void BoardView::mouseDoubleClickEvent(QMouseEvent *event)
{				
	auto *item = itemAt(event->pos());

	if (!item)
		return;

	qDebug() << item;

	if (m_board->canBringOn())
		emit bringOn();
}
