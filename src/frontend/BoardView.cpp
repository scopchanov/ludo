#include "BoardView.h"
#include "BoardScene.h"
#include "ArrowItem.h"
#include "FieldItem.h"
#include <QMouseEvent>
#include <QDebug>

BoardView::BoardView(QWidget *parent) :
	QGraphicsView{parent},
	m_board(new BoardScene(this))
{
	setBackgroundBrush(QBrush(0xBDBDBD));
	setFrameStyle(QFrame::NoFrame);
	setAlignment(Qt::AlignCenter);
	setScene(m_board);
}

BoardScene *BoardView::board() const
{
	return m_board;
}

void BoardView::mousePressEvent(QMouseEvent *event)
{
    auto *item{itemAt(event->pos())};

	if (!item)
		return;

	switch (item->type()) {
	case 65536:
		fieldClicked(static_cast<FieldItem *>(item));
		break;
	case 65538:
		arrowClicked(static_cast<ArrowItem *>(item));
		break;
	default:
		break;
	}
}

void BoardView::fieldClicked(FieldItem *field)
{
	if (field->isHighlighted())
		emit movePawn(field->number());
}

void BoardView::arrowClicked(ArrowItem *arrow)
{
	if (!m_board->canBringIn())
		return;

	if (!arrow->isHighlighted())
		return;

	m_board->enableBringIn(false);
	emit bringPawnIn();
}
