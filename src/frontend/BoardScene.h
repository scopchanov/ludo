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
class TileItem;
class BaseItem;
class ArrowItem;
class HomeItem;
class PlayerItem;

class BoardScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit BoardScene(QObject *parent = nullptr);

	void highlightPlayer(int playerId);
	void setPlayerText(int playerId, const QString &str);

	void setScore(int value);

	void clearHighlight();
    void clearPlayersText();
	void updateBoard(const QJsonObject &json);
	void updateWinners(const QJsonArray &winners);

public slots:
	void updateArrows(bool canBringIn);
    void showMoves(const QList<int> &moves);

private:
	void createPath();
	void createBaseAreas();
	void createHomeAreas();
    void createTiles();
    void createPlayers();
	int playerColor(int playerId) const;
	bool isCurrentArrow(ArrowItem *arrow) const;
	bool haveSameIndex(PlayerItem *player, ArrowItem *arrow) const;

	DiceItem *_diceItem;
	QList<TileItem *> _tileItems;
	QList<BaseItem *> _baseItems;
	QList<HomeItem *> _homeItems;
	QList<ArrowItem *> _arrowItems;
	QList<PlayerItem *> _playerItems;
};

#endif // BOARDSCENE_H
