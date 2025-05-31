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

#ifndef PATH_H
#define PATH_H

#include <QObject>

class Tile;

using Player = std::optional<int>;

class Path : public QObject
{
	Q_OBJECT
public:
	explicit Path(int tileCount, QObject *parent = nullptr);
	
	Player playerAt(int tileIndex) const;
    bool setPlayerAt(int player, int tileIndex);

	int tileCount() const;
	bool isTileOccupiedBy(int player, int srcTileIndex) const;

	bool canBringPawnIn(int player, int tileIndex);
	bool canMove(int player, int srcTileIndex, int steps) const;
	
	int distance(int fromTileIndex, int toTileIndex);

	bool bringPawnIn(int player, int tileIndex);
	bool movePawn(int player, int srcTileIndex, int steps);
	Player removePlayerAt(int tileIndex);
	void clear();

private:
	bool occupy(int player, Tile *tile);
	bool canOccupy(int player, Tile *tile) const;
	Tile *tile(int index) const;
	bool isFullyOccupied() const;
	int wrappedIndex(int index) const;
	bool isValidTile(int index) const;

	int _pawnCount;
	QList<Tile *> _tiles;

signals:
	void pawnBusted(int player);
};

#endif // PATH_H
