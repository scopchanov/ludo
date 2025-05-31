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

#ifndef BOARD_H
#define BOARD_H

#include <QObject>

class Path;
class Pawn;
class Base;

class Board : public QObject
{
	Q_OBJECT
public:
	explicit Board(QObject *parent = nullptr);

	Path *track() const;

	QJsonObject state() const;
	void setState(const QJsonObject &json);

	bool canBringIn(int player) const;
	QList<int> findPossibleMoves(int player, int score);

	bool bringPawnIn(int player);
	bool movePawn(int player, int srcTileIndex, int steps);
	bool takePawnOut(int tileIndex, int score);

	void init();
	void clear();

private:
	void setPathTileState(Path *path, const QJsonObject &json);
	int entryTileIndex(int player) const;
	QList<QJsonObject> toObjects(const QJsonArray &array);

	Path *_track;
	QList<Base *> _baseAreas;
	QList<Path *> _homeAreas;

private slots:
	void onPawnBusted(int player);

signals:
	void playerEscaped(int player);

	friend class MoveAction;
};

#endif // BOARD_H
