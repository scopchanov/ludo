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

	bool canBringIn() const;
	int currentPlayerId() const;
	void setCurrentPlayerId(int currentPlayerId);
    void setCurrentPlayerText(const QString &str);

	void setScore(int value);

	void clearHighlight();
	void updateBoard(const QJsonObject &json);

public slots:
	void enableBringIn(bool canBringIn);
	void changePawnCount(int playerId, int pawnCount);
	void highlightFields(const QList<int> &moves);

private:
	void createPath();
	void createIslands();
	void createHomes();
	void createFields();
    void createPlayers();
	int playerColor(int playerId) const;

	QList<FieldItem *> m_fieldItems;
	QList<SpawnItem *> m_spawnItems;
	QList<ArrowItem *> m_arrowItems;
	QList<PlayerItem *> m_playerItems;
	QList<HomeItem *> m_homeItems;
	ScoreItem *m_scoreItem;
	int m_currentPlayerId;
	bool m_canBringPawnIn;
};

#endif // BOARDSCENE_H
