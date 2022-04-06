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
	void clearHighlight();
	void updateBoard(const QList<QPair<int, int>> &pawns);

public slots:
	void enableBringOn(bool canBringOn);
	void changePawnCount(int playerId, int pawnCount);
	void highlightFields(const QList<int> &moves);

private:
	void createPath();
	void createPlayers();
	void createFields();

	QList<PlayerItem *> m_playerItems;
	QList<FieldItem *> m_fieldItems;
	bool m_canBringPawnOn;
};

#endif // BOARDSCENE_H
