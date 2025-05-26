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

#include "ArrowItem.h"
#include "UiGlobals.h"
#include <QPainter>

ArrowItem::ArrowItem(QGraphicsItem *parent) :
	QGraphicsPathItem{parent},
	_number{0},
	_highlighted{false}
{
	QPainterPath p;

	p.addPolygon(QVector<QPointF>{
                     QPoint(-20, -10), QPoint(5, -10), QPoint(5, -20),
					 QPoint(30, 0), QPoint(5, 20), QPoint(5, 10),
                     QPoint(-20, 10), QPoint(-20, -10)
				 });

	setPath(p);
	setPen(QPen(QBrush(0x313131), 3, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
}

int ArrowItem::number() const
{
	return _number;
}

void ArrowItem::setNumber(int number)
{
	_number = number;
}

const QColor &ArrowItem::color() const
{
	return brush().color();
}

void ArrowItem::setColor(const QColor &color)
{
	setBrush(QBrush(color));
	update();
}

bool ArrowItem::isHighlighted() const
{
	return _highlighted;
}

void ArrowItem::setHighlighted(bool highlighted)
{
	_highlighted = highlighted;
	update();
}

void ArrowItem::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem */*option*/,
					  QWidget */*widget*/)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(_highlighted ? QPen(QBrush(0xF57C00), 5) : pen());
	painter->setBrush(brush());
	painter->drawPath(path());
	painter->restore();
}

int ArrowItem::type() const
{
	return IT_Arrow;
}
