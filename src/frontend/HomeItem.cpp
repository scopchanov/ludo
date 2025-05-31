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

#include "HomeItem.h"
#include "TileItem.h"
#include "UiGlobals.h"
#include <QJsonObject>
#include <QJsonArray>

HomeItem::HomeItem(const QColor &color, QGraphicsItem *parent) :
	QGraphicsRectItem{parent}
{
    for (int n{0}; n < 4; n++) {
		auto *tile{new TileItem(this)};

		tile->setNumber(n);
		tile->setColor(color);
		tile->setPos(0, 105 - 70*n);

		_tileItems.append(tile);
	}
}

void HomeItem::updateItem(const QJsonArray &json)
{
	for (auto *tile : std::as_const(_tileItems))
		tile->setPawnColor(QColor());

	for (const auto &value : json) {
		const QJsonObject &tileSettings{value.toObject()};
		const QColor &color{_tileItems.first()->color()};
		int tileIndex{tileSettings.value("index").toInt()};

		_tileItems.at(tileIndex)->setPawnColor(color);
	}
}

int HomeItem::type() const
{
	return IT_Home;
}
