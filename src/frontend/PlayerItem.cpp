#include "PlayerItem.h"
#include <QPainter>

PlayerItem::PlayerItem(QGraphicsItem *parent) :
	QGraphicsEllipseItem{parent},
	m_number{0},
	m_highlighted{false}
{
	setRect(-70, -70, 140, 140);
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

bool PlayerItem::highlighted() const
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
	painter->setPen(m_highlighted ? QPen(QBrush(0x7B1FA2), 5) : pen());
	painter->setBrush(brush());
	painter->drawEllipse(rect());
	painter->restore();
}
