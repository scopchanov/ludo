#include "SpawnItem.h"
#include "FieldItem.h"
#include <QPainter>
#include <QDebug>

SpawnItem::SpawnItem(int playerId, const QColor &color, QGraphicsItem *parent) :
	QGraphicsRectItem{parent},
	m_playerId{playerId}
{
	for (int n = 0; n < 4; n++) {
		auto *field = new FieldItem(this);

		field->setNumber(n);
		field->setPos(70*(n / 2) - 35, 70*(n % 2) - 35);
		field->setFlags(ItemStacksBehindParent);
		field->setColor(color);
		field->setPawnColor(color);

		m_fields.append(field);
	}

	setRect(-70, -70, 140, 140);
}

int SpawnItem::playerId() const
{
	return m_playerId;
}

QColor SpawnItem::color() const
{
	return m_fields.first()->color();
}

void SpawnItem::setPawnCount(int n)
{
	for (auto *field : qAsConst(m_fields))
		field->setPawnColor(m_fields.indexOf(field) < n
							? m_fields.first()->color()
							: QColor());
}

void SpawnItem::paint(QPainter *painter,
					   const QStyleOptionGraphicsItem */*option*/,
					   QWidget */*widget*/)
{

}

int SpawnItem::type() const
{
	return QGraphicsItem::UserType + 1;
}
