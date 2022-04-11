#include "HomeItem.h"
#include "FieldItem.h"
#include <QJsonObject>
#include <QJsonArray>

HomeItem::HomeItem(const QColor &color, QGraphicsItem *parent) :
	QGraphicsRectItem{parent}
{
	for (int n = 0; n < 4; n++) {
		auto *field = new FieldItem(this);

		field->setNumber(n);
		field->setColor(color);
		field->setPos(0, 105 - 70*n);

		m_fieldItems.append(field);
	}
}

void HomeItem::updateItem(const QJsonArray &fields)
{
	for (auto *field : qAsConst(m_fieldItems))
		field->setPawnColor(QColor());

	for (const auto &value : fields) {
		const QJsonObject &field{value.toObject()};
		const QColor &color{m_fieldItems.first()->color()};
		int fieldNumber = field.value("number").toInt();

		m_fieldItems.at(fieldNumber)->setPawnColor(color);
	}
}
