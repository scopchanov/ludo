#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>

class BoardScene;
class ArrowItem;
class FieldItem;

class BoardView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit BoardView(QWidget *parent = nullptr);

	BoardScene *board() const;

protected:
	void mousePressEvent(QMouseEvent *event) override;

private:
	void fieldClicked(FieldItem *field);
	void arrowClicked(ArrowItem *arrow);

	BoardScene *m_board;

signals:
	void bringPawnIn();
	void movePawn(int srcField);
};

#endif // BOARDVIEW_H
