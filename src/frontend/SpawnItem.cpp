#include "SpawnItem.h"
#include "FieldItem.h"
#include <QPainter>
#include <QDebug>

SpawnItem::SpawnItem(int playerId, QGraphicsItem *parent) :
	QGraphicsRectItem{parent},
	m_playerId{playerId}
{
	for (int n = 0; n < 4; n++) {
		auto *field = new FieldItem(this);

		field->setNumber(n);
		field->setPos(70*(n / 2) - 35, 70*(n % 2) - 35);
		field->setFlags(ItemStacksBehindParent);
		field->setColor(idToColor(playerId));
		field->setPawnColor(idToColor(playerId));

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

int SpawnItem:: idToColor(int playerId) const
{
	return QList<int>{0x1976D2, 0xFBC02D, 0x388E3C, 0xD32F2F}.at(playerId);
}
