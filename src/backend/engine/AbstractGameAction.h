#ifndef ABSTRACTGAMEACTION_H
#define ABSTRACTGAMEACTION_H

class Board;

class AbstractGameAction
{
public:
	explicit AbstractGameAction(Board *board);

	virtual bool isPossible() const = 0;
	virtual bool trigger() = 0;

protected:
	Board *board() const;

private:
	Board *_board;
};

#endif // ABSTRACTGAMEACTION_H
