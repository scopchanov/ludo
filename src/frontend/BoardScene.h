#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include <QGraphicsScene>

class FieldItem;
class PlayerItem;
class ArrowItem;

class BoardScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit BoardScene(QObject *parent = nullptr);

	bool canBringOn() const;
	int currentPlayerId() const;
	void setCurrentPlayerId(int currentPlayerId);

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

	QList<FieldItem *> m_fieldItems;
	QList<PlayerItem *> m_playerItems;
	QList<ArrowItem *> m_arrowItems;
	int m_currentPlayerId;
	bool m_canBringPawnOn;
};

#endif // BOARDSCENE_H
