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

#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsEllipseItem>

class PlayerItem : public QGraphicsEllipseItem
{
public:
	explicit PlayerItem(QGraphicsItem *parent = nullptr);

	int number() const;
    void setNumber(int n);
	const QColor &color() const;
    void setColor(const QColor &c);
    QString text() const;
    void setText(const QString &str);
	void setPlace(int place);
	bool isHighlighted() const;
    void setHighlighted(bool value);

    void clearText();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
			   QWidget *) override;
	int type() const override;

private:
	int _number;
	bool _highlighted;
	QGraphicsTextItem *_label;
	QGraphicsTextItem *_place;
};

#endif // PLAYERITEM_H
