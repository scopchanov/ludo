#include "ArrowItem.h"
#include <QPainter>

ArrowItem::ArrowItem(QGraphicsItem *parent) :
	QGraphicsPathItem{parent},
	m_number{0},
	m_highlighted{false}
{
	QPainterPath p;

	p.addPolygon(QVector<QPointF>{
					 QPoint(-25, -10), QPoint(5, -10), QPoint(5, -20),
					 QPoint(30, 0), QPoint(5, 20), QPoint(5, 10),
					 QPoint(-25, 10), QPoint(-25, -10)
				 });

	setPath(p);
	setPen(QPen(QBrush(0x313131), 3, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
}

int ArrowItem::number() const
{
	return m_number;
}

void ArrowItem::setNumber(int number)
{
	m_number = number;
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
	return m_highlighted;
}

void ArrowItem::setHighlighted(bool highlighted)
{
	m_highlighted = highlighted;
	update();
}

void ArrowItem::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem */*option*/,
					  QWidget */*widget*/)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(m_highlighted ? QPen(QBrush(0x7E57C2), 5) : pen());
	painter->setBrush(brush());
	painter->drawPath(path());
	painter->restore();
}

int ArrowItem::type() const
{
	return QGraphicsItem::UserType + 2;
}
