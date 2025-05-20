#include "PlayerItem.h"
#include <QPainter>

PlayerItem::PlayerItem(QGraphicsItem *parent) :
	QGraphicsEllipseItem{parent},
	_number{0},
    _highlighted{false},
    _label{new QGraphicsTextItem(this)}
{
    setRect(-65, -65, 130, 130);
	setPen(QPen(QBrush(0x313131), 3));
	setBrush(QBrush(Qt::white));

    _label->setPos(-60, 75);
}

int PlayerItem::number() const
{
	return _number;
}

void PlayerItem::setNumber(int n)
{
    _number = n;
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
    return _label->toPlainText();
}

void PlayerItem::setText(const QString &str)
{
    _label->setPlainText(str);
}

bool PlayerItem::isHighlighted() const
{
	return _highlighted;
}

void PlayerItem::setHighlighted(bool value)
{
    _highlighted = value;
	update();
}

void PlayerItem::clearText()
{
    _label->setPlainText("");
}

void PlayerItem::paint(QPainter *painter,
					   const QStyleOptionGraphicsItem */*option*/,
					   QWidget */*widget*/)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(_highlighted ? QPen(QBrush(0x7B1FA2), 8) : pen());
	painter->setBrush(brush());
	painter->drawEllipse(rect());
	painter->restore();
}
