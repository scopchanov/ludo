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
#include "FieldItem.h"
#include "UiGlobals.h"
#include <QJsonObject>
#include <QJsonArray>

HomeItem::HomeItem(const QColor &color, QGraphicsItem *parent) :
	QGraphicsRectItem{parent}
{
    for (int n{0}; n < 4; n++) {
        auto *field{new FieldItem(this)};

		field->setNumber(n);
		field->setColor(color);
		field->setPos(0, 105 - 70*n);

		_fieldItems.append(field);
	}
}

void HomeItem::updateItem(const QJsonArray &fields)
{
	for (auto *field : std::as_const(_fieldItems))
		field->setPawnColor(QColor());

	for (const auto &value : fields) {
		const QJsonObject &field{value.toObject()};
		const QColor &color{_fieldItems.first()->color()};
        int fieldNumber{field.value("number").toInt()};

		_fieldItems.at(fieldNumber)->setPawnColor(color);
	}
}

int HomeItem::type() const
{
	return IT_Home;
}
