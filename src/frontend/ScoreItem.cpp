#include "ScoreItem.h"
#include <QPainter>

ScoreItem::ScoreItem(QGraphicsItem *parent) :
	QGraphicsRectItem{parent},
	_score{0}
{
	setRect(-30, -30, 60, 60);
}

int ScoreItem::score() const
{
	return _score;
}

void ScoreItem::setScore(int value)
{
	_score = value;
	update();
}

void ScoreItem::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem */*option*/,
					  QWidget */*widget*/)
{
	if (_score)
		painter->drawText(rect(), Qt::AlignCenter | Qt::TextSingleLine,
						  QString::number(_score));
}
