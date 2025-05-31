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

#include "BaseItem.h"
#include "TileItem.h"
#include "UiGlobals.h"
#include <QPainter>

BaseItem::BaseItem(int playerId, const QColor &color, QGraphicsItem *parent) :
	QGraphicsRectItem{parent},
	_playerId{playerId}
{
	for (int n{0}; n < 4; n++) {
        auto *field{new TileItem(this)};

        field->setNumber(n);
		field->setPos(n % 2 ? 105 : 35, n < 2 ? 35 : -35);
		field->setFlags(ItemStacksBehindParent);
		field->setColor(color);
		field->setPawnColor(color);

		_fields.append(field);
	}

	setRect(-70, -70, 140, 140);
}

int BaseItem::playerId() const
{
	return _playerId;
}

QColor BaseItem::color() const
{
	return _fields.first()->color();
}

void BaseItem::setPawnCount(int n)
{
	for (auto *field : std::as_const(_fields))
		field->setPawnColor(_fields.indexOf(field) < n
							? _fields.first()->color()
							: QColor());
}

void BaseItem::paint(QPainter */*painter*/,
					   const QStyleOptionGraphicsItem */*option*/,
					   QWidget */*widget*/)
{

}

int BaseItem::type() const
{
	return IT_Base;
}
