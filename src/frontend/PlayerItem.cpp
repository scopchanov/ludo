/**
MIT License

Copyright (c) 2022-2025 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
