#ifndef DICEITEM_H
#define DICEITEM_H

#include <QGraphicsRectItem>

class DiceItem : public QGraphicsRectItem
{
public:
	explicit DiceItem(QGraphicsItem *parent = nullptr);

	int score() const;
	void setScore(int value);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

private:
	void drawOne(QPainter *painter);
	void drawTwo(QPainter *painter);
	void drawThree(QPainter *painter);
	void drawFour(QPainter *painter);
	void drawFive(QPainter *painter);
	void drawSix(QPainter *painter);
	void drawDot(QPainter *painter, const QPointF &p);

	int _score;
};

#endif // DICEITEM_H
