#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsEllipseItem>

class PlayerItem : public QGraphicsEllipseItem
{
public:
	explicit PlayerItem(QGraphicsItem *parent = nullptr);

	int number() const;
    void setNumber(int n);
	const QColor &color() const;
    void setColor(const QColor &c);
    QString text() const;
    void setText(const QString &str);
	bool isHighlighted() const;
    void setHighlighted(bool value);

    void clearText();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
			   QWidget *) override;

private:
	int _number;
	bool _highlighted;
	QGraphicsTextItem *_label;
};

#endif // PLAYERITEM_H
