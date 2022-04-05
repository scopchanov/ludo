#include "FieldItem.h"
#include <QPainter>

FieldItem::FieldItem(QGraphicsItem *parent) :
	QGraphicsEllipseItem(parent),
	m_number{0}
{
	setRect(-30, -30, 60, 60);
	setPen(QPen(QBrush(0x313131), 4));
	setColor(0xFFF3E0);
}

int FieldItem::number() const
{
	return m_number;
}

void FieldItem::setNumber(int number)
{
	m_number = number;
}

const QColor &FieldItem::color() const
{
	return brush().color();
}

void FieldItem::setColor(const QColor &color)
{
	setBrush(QBrush(color));
}

void FieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
					  QWidget *widget)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(pen());
	painter->setBrush(brush());
	painter->drawEllipse(rect());
	painter->restore();
}
