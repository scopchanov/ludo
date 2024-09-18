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

    void clear();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
			   QWidget *) override;

private:
	int m_number;
	bool m_highlighted;
    QGraphicsTextItem *m_label;
};

#endif // PLAYERITEM_H
