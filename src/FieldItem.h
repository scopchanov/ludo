#ifndef FIELDITEM_H
#define FIELDITEM_H

#include <QGraphicsEllipseItem>

class FieldItem : public QGraphicsEllipseItem
{
public:
	explicit FieldItem(QGraphicsItem *parent = nullptr);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

	int number() const;
	void setNumber(int number);
	bool selected() const;
	void setSelected(bool selected);
	const QColor &color() const;
	void setColor(const QColor &color);
	void setOccupationColor(const QColor &color);

	int type() const override;

private:
	int m_number;
	bool m_selected;
	QColor m_occupationColor;
};

#endif // FIELDITEM_H
