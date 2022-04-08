#ifndef SPAWNITEM_H
#define SPAWNITEM_H

#include <QGraphicsRectItem>

class FieldItem;

class SpawnItem : public QGraphicsRectItem
{
public:
	explicit SpawnItem(int playerId, QGraphicsItem *parent = nullptr);

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

#endif // SPAWNITEM_H
