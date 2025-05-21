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

#include "FieldItem.h"
#include <QPainter>

FieldItem::FieldItem(QGraphicsItem *parent) :
	QGraphicsEllipseItem(parent),
	_number{0},
	_highlighted{false}
{
	setRect(-30, -30, 60, 60);
	setPen(QPen(QBrush(0x313131), 4));
	setColor(0xEEEEEE);
}

int FieldItem::number() const
{
	return _number;
}

void FieldItem::setNumber(int n)
{
	_number = n;
}

bool FieldItem::isHighlighted() const
{
	return _highlighted;
}

void FieldItem::setHighlighted(bool value)
{
	_highlighted = value;
	update();
}

const QColor &FieldItem::color() const
{
	return brush().color();
}

void FieldItem::setColor(const QColor &color)
{
	setBrush(QBrush(color));
	update();
}

void FieldItem::setPawnColor(const QColor &color)
{
	_pawnColor = color;
	update();
}

int FieldItem::type() const
{
	return QGraphicsItem::UserType;
}

void FieldItem::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem */*option*/,
					  QWidget */*widget*/)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(pen());
	painter->setBrush(brush());
	painter->drawEllipse(rect());

	if (_pawnColor.isValid()) {
		painter->setPen(_highlighted ? QPen(QBrush(0xF57C00), 5)
									  : QPen(QBrush(0x424242), 3));
		painter->setBrush(_pawnColor.lighter(130));
		painter->drawEllipse(rect().adjusted(10, 10, -10, -10));
	}

//	painter->drawText(rect(), Qt::AlignCenter | Qt::TextSingleLine,
//					  QString::number(m_number));

	painter->restore();
}
