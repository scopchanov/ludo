#ifndef HOMEITEM_H
#define HOMEITEM_H

#include <QGraphicsRectItem>

class HomeItem : public QGraphicsRectItem
{
public:
	explicit HomeItem(const QColor &color, QGraphicsItem *parent = nullptr);
};

#endif // HOMEITEM_H
