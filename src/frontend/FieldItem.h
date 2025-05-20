#ifndef FIELDITEM_H
#define FIELDITEM_H

#include <QGraphicsEllipseItem>

class FieldItem : public QGraphicsEllipseItem
{
public:
	explicit FieldItem(QGraphicsItem *parent = nullptr);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
			   QWidget *) override;

	int number() const;
	void setNumber(int n);
	bool isHighlighted() const;
	void setHighlighted(bool value);
	const QColor &color() const;
	void setColor(const QColor &color);
	void setPawnColor(const QColor &color);

	int type() const override;

private:
	int _number;
	bool _highlighted;
	QColor _pawnColor;
};

#endif // FIELDITEM_H
