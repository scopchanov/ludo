#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsRectItem>

class FieldItem;

class PlayerItem : public QGraphicsRectItem
{
public:
	explicit PlayerItem(int playerId, QGraphicsItem *parent = nullptr);

	int playerId() const;
	QColor color() const;
	void setPawnCount(int n);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
			   QWidget *) override;
	int type() const override;

private:
	int idToColor(int playerId) const;

	int m_playerId;
	QList<FieldItem *> m_fields;
};

#endif // PLAYERITEM_H
