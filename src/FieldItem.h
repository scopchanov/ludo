#ifndef FIELDITEM_H
#define FIELDITEM_H

#include <QGraphicsPathItem>

class FieldItem : public QGraphicsPathItem
{
public:
	explicit FieldItem(QGraphicsItem *parent = nullptr);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			   QWidget *widget) override;

	int number() const;
	void setNumber(int number);

	const QColor &color() const;
	void setColor(const QColor &color);

private:
	int m_number;
	QColor m_color;
};

#endif // FIELDITEM_H
