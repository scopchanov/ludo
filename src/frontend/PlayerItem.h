#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsEllipseItem>

class PlayerItem : public QGraphicsEllipseItem
{
public:
	explicit PlayerItem(QGraphicsItem *parent = nullptr);

	int number() const;
	void setNumber(int number);
	bool highlighted() const;
	void setHighlighted(bool highlighted);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
			   QWidget *) override;

private:
	int m_number;
	bool m_highlighted;
};

#endif // PLAYERITEM_H
