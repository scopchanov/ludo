#include "PlayerItem.h"
#include <QPainter>

PlayerItem::PlayerItem(QGraphicsItem *parent) :
	QGraphicsEllipseItem{parent},
	m_number{0},
	m_highlighted{false}
{
	setRect(-70, -70, 140, 140);
	setPen(QPen(QBrush(0x313131), 3));
	setBrush(QBrush(Qt::white));
}

int PlayerItem::number() const
{
	return m_number;
}

void PlayerItem::setNumber(int number)
{
	m_number = number;
}

const QColor &PlayerItem::color() const
{
	return brush().color();
}

void PlayerItem::setColor(const QColor &color)
{
	setBrush(QBrush(color));
	update();
}

bool PlayerItem::isHighlighted() const
{
	return m_highlighted;
}

void PlayerItem::setHighlighted(bool highlighted)
{
	m_highlighted = highlighted;
	update();
}

void PlayerItem::paint(QPainter *painter,
					   const QStyleOptionGraphicsItem */*option*/,
					   QWidget */*widget*/)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(m_highlighted ? QPen(QBrush(0x7E57C2), 8) : pen());
	painter->setBrush(brush());
	painter->drawEllipse(rect());
	painter->restore();
}
