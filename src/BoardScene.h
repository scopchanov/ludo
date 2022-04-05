#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include <QGraphicsScene>

class PlayerItem;
class FieldItem;

class BoardScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit BoardScene(QObject *parent = nullptr);

	bool canBringOn() const;
	void enableBringOn(bool canBringOn);

private:
	void createPath();
	void createPlayers(const QList<int> &colors);
	void createFields(const QList<int> &colors);

	QList<PlayerItem *> m_playerItems;
	QList<FieldItem *> m_fieldItems;
	bool m_canBringPawnOn;
};

#endif // BOARDSCENE_H
