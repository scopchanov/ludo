#ifndef SCOREITEM_H
#define SCOREITEM_H

#include <QGraphicsRectItem>

class ScoreItem : public QGraphicsRectItem
{
public:
	explicit ScoreItem(QGraphicsItem *parent = nullptr);

	int score() const;
	void setScore(int value);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
	int _score;
};

#endif // SCOREITEM_H
