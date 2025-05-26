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

#ifndef DICEITEM_H
#define DICEITEM_H

#include <QGraphicsRectItem>

class DiceItem : public QGraphicsRectItem
{
public:
	explicit DiceItem(QGraphicsItem *parent = nullptr);

	int score() const;
	void setScore(int value);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;
	int type() const override;

private:
	void drawOne(QPainter *painter);
	void drawTwo(QPainter *painter);
	void drawThree(QPainter *painter);
	void drawFour(QPainter *painter);
	void drawFive(QPainter *painter);
	void drawSix(QPainter *painter);
	void drawDot(QPainter *painter, const QPointF &p);

	int _score;
};

#endif // DICEITEM_H
