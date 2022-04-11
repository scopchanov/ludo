#include "ScoreItem.h"
#include <QPainter>

ScoreItem::ScoreItem(QGraphicsItem *parent) :
	QGraphicsRectItem{parent},
	m_score{0}
{
	setRect(-30, -30, 60, 60);
}

int ScoreItem::score() const
{
	return m_score;
}

void ScoreItem::setScore(int value)
{
	m_score = value;
	update();
}

void ScoreItem::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem */*option*/,
					  QWidget */*widget*/)
{
	if (m_score)
		painter->drawText(rect(), Qt::AlignCenter | Qt::TextSingleLine,
						  QString::number(m_score));
}
