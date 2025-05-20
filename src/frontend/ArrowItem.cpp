#include "ArrowItem.h"
#include <QPainter>

ArrowItem::ArrowItem(QGraphicsItem *parent) :
	QGraphicsPathItem{parent},
	_number{0},
	_highlighted{false}
{
	QPainterPath p;

	p.addPolygon(QVector<QPointF>{
                     QPoint(-20, -10), QPoint(5, -10), QPoint(5, -20),
					 QPoint(30, 0), QPoint(5, 20), QPoint(5, 10),
                     QPoint(-20, 10), QPoint(-20, -10)
				 });

	setPath(p);
	setPen(QPen(QBrush(0x313131), 3, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
}

int ArrowItem::number() const
{
	return _number;
}

void ArrowItem::setNumber(int number)
{
	_number = number;
}

const QColor &ArrowItem::color() const
{
	return brush().color();
}

void ArrowItem::setColor(const QColor &color)
{
	setBrush(QBrush(color));
	update();
}

bool ArrowItem::isHighlighted() const
{
	return _highlighted;
}

void ArrowItem::setHighlighted(bool highlighted)
{
	_highlighted = highlighted;
	update();
}

void ArrowItem::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem */*option*/,
					  QWidget */*widget*/)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(_highlighted ? QPen(QBrush(0xF57C00), 5) : pen());
	painter->setBrush(brush());
	painter->drawPath(path());
	painter->restore();
}

int ArrowItem::type() const
{
	return QGraphicsItem::UserType + 2;
}
