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
    void clearPlayersText();
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

	QList<FieldItem *> _fieldItems;
	QList<SpawnItem *> _spawnItems;
	QList<ArrowItem *> _arrowItems;
	QList<PlayerItem *> _playerItems;
	QList<HomeItem *> _homeItems;
	ScoreItem *_scoreItem;
	int _currentPlayerId;
	bool _canBringPawnIn;
};

#endif // BOARDSCENE_H
