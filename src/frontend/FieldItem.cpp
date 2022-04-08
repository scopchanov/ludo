#include "FieldItem.h"
#include <QPainter>

FieldItem::FieldItem(QGraphicsItem *parent) :
	QGraphicsEllipseItem(parent),
	m_number{0},
	m_highlighted{false}
{
	setRect(-30, -30, 60, 60);
	setPen(QPen(QBrush(0x313131), 4));
	setColor(0xFFF3E0);
}

int FieldItem::number() const
{
	return m_number;
}

void FieldItem::setNumber(int n)
{
	m_number = n;
}

bool FieldItem::isHighlighted() const
{
	return m_highlighted;
}

void FieldItem::setHighlighted(bool value)
{
	m_highlighted = value;
	update();
}

const QColor &FieldItem::color() const
{
	return brush().color();
}

void FieldItem::setColor(const QColor &color)
{
	setBrush(QBrush(color));
	update();
}

void FieldItem::setPawnColor(const QColor &color)
{
	m_pawnColor = color;
	update();
}

int FieldItem::type() const
{
	return QGraphicsItem::UserType;
}

void FieldItem::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem */*option*/,
					  QWidget */*widget*/)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(pen());
	painter->setBrush(brush());
	painter->drawEllipse(rect());

	if (m_pawnColor.isValid()) {
		painter->setPen(m_highlighted ? QPen(QBrush(0x7B1FA2), 5)
									  : QPen(QBrush(0x424242), 3));
		painter->setBrush(m_pawnColor.lighter(130));
		painter->drawEllipse(rect().adjusted(10, 10, -10, -10));
	}

//	painter->drawText(rect(), Qt::AlignCenter | Qt::TextSingleLine,
//					  QString::number(m_number));

	painter->restore();
}
