#include "DiceItem.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>

DiceItem::DiceItem(QGraphicsItem *parent) :
	QGraphicsRectItem{parent},
	_score{0}
{
	setRect(-30, -30, 60, 60);
}

int DiceItem::score() const
{
	return _score;
}

void DiceItem::setScore(int value)
{
	_score = value;
	update();
}

void DiceItem::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem *option,
					  QWidget */*widget*/)
{
	if (!_score)
		return;

	painter->save();
	painter->setClipping(true);
	painter->setClipRect(option->rect);
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(QPen(QBrush(0x313131), 2));
	painter->setBrush(QBrush(0xFFFFFF));
	painter->drawRoundedRect(rect().adjusted(5, 5, -5, -5), 4, 4);

	switch (_score) {
	case 1:
		drawOne(painter);
		break;
	case 2:
		drawTwo(painter);
		break;
	case 3:
		drawThree(painter);
		break;
	case 4:
		drawFour(painter);
		break;
	case 5:
		drawFive(painter);
		break;
	case 6:
		drawSix(painter);
		break;
	}

	painter->restore();
}

void DiceItem::drawOne(QPainter *painter)
{
	drawDot(painter, rect().topLeft() + QPointF(30, 30));
}

void DiceItem::drawTwo(QPainter *painter)
{
	drawDot(painter, rect().topLeft() + QPointF(16, 44));
	drawDot(painter, rect().topLeft() + QPointF(44, 16));
}

void DiceItem::drawThree(QPainter *painter)
{
	drawDot(painter, rect().topLeft() + QPointF(16, 44));
	drawDot(painter, rect().topLeft() + QPointF(30, 30));
	drawDot(painter, rect().topLeft() + QPointF(44, 16));
}

void DiceItem::drawFour(QPainter *painter)
{
	drawDot(painter, rect().topLeft() + QPointF(16, 16));
	drawDot(painter, rect().topLeft() + QPointF(16, 44));
	drawDot(painter, rect().topLeft() + QPointF(44, 16));
	drawDot(painter, rect().topLeft() + QPointF(44, 44));
}

void DiceItem::drawFive(QPainter *painter)
{
	drawDot(painter, rect().topLeft() + QPointF(16, 16));
	drawDot(painter, rect().topLeft() + QPointF(16, 44));
	drawDot(painter, rect().topLeft() + QPointF(44, 16));
	drawDot(painter, rect().topLeft() + QPointF(44, 44));
	drawDot(painter, rect().topLeft() + QPointF(30, 30));
}

void DiceItem::drawSix(QPainter *painter)
{
	drawDot(painter, rect().topLeft() + QPointF(16, 16));
	drawDot(painter, rect().topLeft() + QPointF(16, 30));
	drawDot(painter, rect().topLeft() + QPointF(16, 44));
	drawDot(painter, rect().topLeft() + QPointF(44, 16));
	drawDot(painter, rect().topLeft() + QPointF(44, 30));
	drawDot(painter, rect().topLeft() + QPointF(44, 44));
}

void DiceItem::drawDot(QPainter *painter, const QPointF &p)
{
	painter->setBrush(QBrush(0x313131));
	painter->drawEllipse(p, 4, 4);
}
