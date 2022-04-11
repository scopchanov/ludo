#ifndef HOMEITEM_H
#define HOMEITEM_H

#include <QGraphicsRectItem>

class FieldItem;

class HomeItem : public QGraphicsRectItem
{
public:
	explicit HomeItem(const QColor &color, QGraphicsItem *parent = nullptr);

	void updateItem(const QJsonArray &fields);

private:
	QList<FieldItem *> m_fieldItems;
};

#endif // HOMEITEM_H
