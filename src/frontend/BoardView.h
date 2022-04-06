#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>

class BoardScene;
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
	void arrowClicked();

	BoardScene *m_board;

signals:
	void bringPawnOn();
	void movePawn(int srcField);
};

#endif // BOARDVIEW_H
