#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>

class BoardScene;

class BoardView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit BoardView(QWidget *parent = nullptr);

	BoardScene *board() const;

protected:
//	void mousePressEvent(QMouseEvent *event) override;
//	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
//	void mouseMoveEvent(QMouseEvent *event) override;

private:
	void createFields();

	BoardScene *m_board;

signals:
	void bringPawnOn();
	void movePawn(int srcField);
};

#endif // BOARDVIEW_H
