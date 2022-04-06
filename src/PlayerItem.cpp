#include "PlayerItem.h"
#include "FieldItem.h"
#include <QPainter>
#include <QDebug>

PlayerItem::PlayerItem(int playerId, QGraphicsItem *parent) :
	QGraphicsRectItem{parent},
	m_playerId{playerId}
{
	for (int n = 0; n < 4; n++) {
		auto *field = new FieldItem(this);

		field->setPos(70*(n / 2) - 35, 70*(n % 2) - 35);
		field->setFlags(ItemStacksBehindParent);
		field->setColor(playerColor(playerId));
		field->setOccupationColor(QColor(playerColor(playerId)));

		m_fields.append(field);
	}

	setRect(-70, -70, 140, 140);
}

int PlayerItem::playerId() const
{
	return m_playerId;
}

QColor PlayerItem::color() const
{
	return m_fields.first()->color();
}

void PlayerItem::setPawnCount(int n)
{
	foo(n);
}

void PlayerItem::paint(QPainter *painter,
					   const QStyleOptionGraphicsItem */*option*/,
					   QWidget */*widget*/)
{

}

int PlayerItem::type() const
{
	return QGraphicsItem::UserType + 1;
}

int PlayerItem:: playerColor(int playerId) const
{
	return QList<int>{0x1976D2, 0xFBC02D, 0x388E3C, 0xD32F2F}.at(playerId);
}

void PlayerItem::foo(int n)
{
	for (auto *field : qAsConst(m_fields)) {
		field->setOccupationColor(m_fields.indexOf(field) < n
								  ? m_fields.first()->color()
								  : QColor());
	}
}
