#include "SpawnItem.h"
#include "FieldItem.h"
#include <QPainter>

SpawnItem::SpawnItem(int playerId, const QColor &color, QGraphicsItem *parent) :
	QGraphicsRectItem{parent},
	_playerId{playerId}
{
	for (int n{0}; n < 4; n++) {
        auto *field{new FieldItem(this)};

        field->setNumber(n);
        field->setPos(n % 2 ? 105 : 35, n < 2 ? 35 : -35);//175 - 70*n);
		field->setFlags(ItemStacksBehindParent);
		field->setColor(color);
		field->setPawnColor(color);

		_fields.append(field);
	}

	setRect(-70, -70, 140, 140);
}

int SpawnItem::playerId() const
{
	return _playerId;
}

QColor SpawnItem::color() const
{
	return _fields.first()->color();
}

void SpawnItem::setPawnCount(int n)
{
    for (auto *field : _fields)
		field->setPawnColor(_fields.indexOf(field) < n
							? _fields.first()->color()
							: QColor());
}

void SpawnItem::paint(QPainter */*painter*/,
					   const QStyleOptionGraphicsItem */*option*/,
					   QWidget */*widget*/)
{

}

int SpawnItem::type() const
{
	return QGraphicsItem::UserType + 1;
}
