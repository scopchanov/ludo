/**
MIT License

Copyright (c) 2022-2025 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include <QGraphicsScene>

class DiceItem;
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
	DiceItem *_diceItem;
	int _currentPlayerId;
	bool _canBringPawnIn;
};

#endif // BOARDSCENE_H
