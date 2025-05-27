#ifndef MOVE_H
#define MOVE_H

#include <QObject>

class Board;
class Pawn;
class Tile;

class Move : public QObject
{
	Q_OBJECT
public:
	explicit Move(Pawn *pawn, int steps, Board *parent = nullptr);

	bool isPossible() const;
	bool make();

private:
	bool exceedsTrackLength() const;
	Tile *trackTile() const;
	Tile *homeTile() const;
	int entryTile(int playerId) const;
	int wrappedIndex(int index) const;

	Board *_board;
	Pawn *_pawn;
	int _steps;
};

#endif // MOVE_H
