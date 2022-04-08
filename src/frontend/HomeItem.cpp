#include "HomeItem.h"
#include "FieldItem.h"

HomeItem::HomeItem(const QColor &color, QGraphicsItem *parent) :
	QGraphicsRectItem{parent}
{
	for (int n = 0; n < 4; n++) {
		auto *field = new FieldItem(this);

		field->setNumber(n);
		field->setColor(color);
		field->setPos(0, 105 - 70*n);
	}
}
