#include "PlayerItem.h"
#include <QPainter>

PlayerItem::PlayerItem(QGraphicsItem *parent) :
	QGraphicsEllipseItem{parent},
	m_number{0},
    m_highlighted{false},
    m_label{new QGraphicsTextItem(this)}
{
	setRect(-70, -70, 140, 140);
	setPen(QPen(QBrush(0x313131), 3));
	setBrush(QBrush(Qt::white));

    m_label->setPos(-60, 75);
}

int PlayerItem::number() const
{
	return m_number;
}

void PlayerItem::setNumber(int n)
{
    m_number = n;
}

const QColor &PlayerItem::color() const
{
	return brush().color();
}

void PlayerItem::setColor(const QColor &c)
{
    setBrush(QBrush(c));
	update();
}

QString PlayerItem::text() const
{
    return m_label->toPlainText();
}

void PlayerItem::setText(const QString &str)
{
    m_label->setPlainText(str);
}

bool PlayerItem::isHighlighted() const
{
	return m_highlighted;
}

void PlayerItem::setHighlighted(bool value)
{
    m_highlighted = value;
	update();
}

void PlayerItem::clear()
{
    m_label->setPlainText("");
}

void PlayerItem::paint(QPainter *painter,
					   const QStyleOptionGraphicsItem */*option*/,
					   QWidget */*widget*/)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(m_highlighted ? QPen(QBrush(0x7B1FA2), 8) : pen());
	painter->setBrush(brush());
	painter->drawEllipse(rect());
	painter->restore();
}
