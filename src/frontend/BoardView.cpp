#include "BoardView.h"
#include "BoardScene.h"
#include "ArrowItem.h"
#include "FieldItem.h"
#include <QMouseEvent>
#include <QDebug>

BoardView::BoardView(QWidget *parent) :
    QGraphicsView{parent},
    _board(new BoardScene(this))
{
    setBackgroundBrush(QBrush(0x757575));
    setFrameStyle(QFrame::NoFrame);
    setAlignment(Qt::AlignCenter);
    setScene(_board);
    setMinimumSize(300, 300);
}

BoardScene *BoardView::board() const
{
    return _board;
}

void BoardView::mousePressEvent(QMouseEvent *event)
{
    auto *item{itemAt(event->pos())};

    if (!item)
        return;

    switch (item->type()) {
    case 65536:
        fieldClicked(static_cast<FieldItem *>(item));
        break;
    case 65538:
        arrowClicked(static_cast<ArrowItem *>(item));
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

void BoardView::fieldClicked(FieldItem *field)
{
    if (field->isHighlighted())
        emit movePawn(field->number());
}

void BoardView::arrowClicked(ArrowItem *arrow)
{
    if (!_board->canBringIn())
        return;

    if (!arrow->isHighlighted())
        return;

    _board->enableBringIn(false);
    emit bringPawnIn();
}
