#include "FieldItem.h"
#include <QPainter>

FieldItem::FieldItem(QGraphicsItem *parent) :
	QGraphicsPathItem(parent),
	m_number{0},
	m_color{0xFFF3E0}
{

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
	return m_color;
}

void FieldItem::setColor(const QColor &color)
{
	m_color = color;
}

void FieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
					  QWidget *widget)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(QPen(QBrush(0x313131), 3));
	painter->setBrush(QBrush(m_color));
	painter->drawEllipse(-30, -30, 60, 60);
	painter->setPen(QPen(QBrush(0x313131), 1));
//	painter->setBrush(QBrush(Qt::white));
//	painter->drawEllipse(-22, -22, 44, 44);
//	painter->drawText(-30, -30, 60, 60, Qt::TextSingleLine | Qt::AlignCenter,
//					  QString::number(m_number));
	painter->restore();
}
