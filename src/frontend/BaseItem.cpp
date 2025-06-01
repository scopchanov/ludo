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

BaseItem::BaseItem(int player, const QColor &color, QGraphicsItem *parent) :
	QGraphicsRectItem{parent},
	_player{player}
{
	for (int n{0}; n < 4; n++) {
		auto *tile{new TileItem(this)};
		int distance{35};
		int x{n % 3 ? -distance : distance};
		int y{n / 2 ? -distance : distance};

		tile->setPos(x, y);
		tile->setNumber(n);
		tile->setFlags(ItemStacksBehindParent);
		tile->setColor(color);
		tile->setPawnColor(color);

		_tiles.append(tile);
	}

	setRect(-70, -70, 140, 140);
}

int BaseItem::player() const
{
	return _player;
}

QColor BaseItem::color() const
{
	return _tiles.first()->color();
}

void BaseItem::setPawnCount(int n)
{
	for (auto *field : std::as_const(_tiles))
		field->setPawnColor(_tiles.indexOf(field) < n
							? _tiles.first()->color()
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
