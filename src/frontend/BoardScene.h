#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include <QGraphicsScene>

class ScoreItem;
class FieldItem;
class SpawnItem;
class ArrowItem;
class HomeItem;
class PlayerItem;

class BoardScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit BoardScene(QObject *parent = nullptr);

	bool canBringOn() const;
	int currentPlayerId() const;
	void setCurrentPlayerId(int currentPlayerId);

	void setScore(int value);

	void clearHighlight();
	void updateBoard(const QList<QPair<int, int>> &pawns);

public slots:
	void enableBringOn(bool canBringOn);
	void changePawnCount(int playerId, int pawnCount);
	void highlightFields(const QList<int> &moves);

private:
	void createPath();
	void createPlayers();
	void createHomes();
	void createFields();
	int playerColor(int playerId) const;

	QList<FieldItem *> m_fieldItems;
	QList<SpawnItem *> m_spawnItems;
	QList<ArrowItem *> m_arrowItems;
	QList<PlayerItem *> m_playerItems;
	QList<HomeItem *> m_homeItems;
	ScoreItem *m_scoreItem;
	int m_currentPlayerId;
	bool m_canBringPawnOn;
};

#endif // BOARDSCENE_H
