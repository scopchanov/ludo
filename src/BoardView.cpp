#include "BoardView.h"
#include "BoardScene.h"
#include "FieldItem.h"
#include <QMouseEvent>
#include <QGraphicsItem>
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

BoardScene *BoardView::board() const
{
	return m_board;
}

void BoardView::mouseDoubleClickEvent(QMouseEvent *event)
{				
	auto *item = itemAt(event->pos());

	if (!item)
		return;


	switch (item->type()) {
	case 65536:
		emit movePawn(static_cast<FieldItem *>(item)->number());
		break;
	case 65537:
		qDebug() << item->type();
		if (m_board->canBringOn()) {
			m_board->enableBringOn(false);
			emit bringPawnOn();
		}
		break;
	default:
		break;
	}

}
