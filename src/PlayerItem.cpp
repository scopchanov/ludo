#include "PlayerItem.h"
#include "FieldItem.h"
#include <QPainter>

PlayerItem::PlayerItem(const QColor &color, QGraphicsItem *parent) :
	QGraphicsRectItem{parent}
{
	for (int n = 0; n < 4; n++) {
		auto *field = new FieldItem(this);

		field->setPos(70*(n / 2) - 35, 70*(n % 2) - 35);
		field->setFlags(ItemStacksBehindParent);
		field->setColor(color);
	}

	setRect(-70, -70, 140, 140);
}

const QColor &PlayerItem::color() const
{
	return m_color;
}

void PlayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
					   QWidget *widget)
{

}
