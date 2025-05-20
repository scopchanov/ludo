#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QGraphicsPathItem>

class ArrowItem : public QGraphicsPathItem
{
public:
	explicit ArrowItem(QGraphicsItem *parent = nullptr);

	int number() const;
	void setNumber(int number);
	const QColor &color() const;
	void setColor(const QColor &color);
	bool isHighlighted() const;
	void setHighlighted(bool highlighted);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
			   QWidget *) override;
	int type() const override;

private:
	int _number;
	bool _highlighted;
};

#endif // ARROWITEM_H
