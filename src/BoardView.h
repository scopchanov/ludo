#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>

class FieldItem;

class BoardView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit BoardView(QWidget *parent = nullptr);

public slots:
	void enableBringOn(bool b);

private:
	QList<FieldItem *> m_fieldItems;

signals:
	void bringOn();
};

#endif // BOARDVIEW_H
