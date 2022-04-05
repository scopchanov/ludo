#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsRectItem>

class PlayerItem : public QGraphicsRectItem
{
public:
	explicit PlayerItem(const QColor &color, QGraphicsItem *parent = nullptr);

	const QColor &color() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			   QWidget *widget) override;

private:
	QColor m_color;
};

#endif // PLAYERITEM_H
