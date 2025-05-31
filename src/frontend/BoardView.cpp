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

#include "BoardView.h"
#include "BoardScene.h"
#include "TileItem.h"
#include "frontend/UiGlobals.h"
#include <QMouseEvent>

BoardView::BoardView(QWidget *parent) :
	QGraphicsView{parent}
{
	setBackgroundBrush(QBrush(0xFFE0B2));
	setFrameStyle(QFrame::NoFrame);
	setAlignment(Qt::AlignCenter);
	setMinimumSize(300, 300);
}

void BoardView::mousePressEvent(QMouseEvent *event)
{
	auto *item{itemAt(event->pos())};

	if (!item)
		return;

	switch (item->type()) {
	case IT_Tile:
		tileClicked(static_cast<TileItem *>(item));
		break;
	case IT_Arrow:
		emit bringPawnIn();
		break;
	default:
		break;
	}
}

void BoardView::resizeEvent(QResizeEvent *event)
{
	fitInView(sceneRect(), Qt::KeepAspectRatio);

	QGraphicsView::resizeEvent(event);
}

void BoardView::tileClicked(TileItem *tile)
{
	if (tile->isHighlighted())
		emit movePawn(tile->number());
}
