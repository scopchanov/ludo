#include "AbstractGameAction.h"

AbstractGameAction::AbstractGameAction(Board *board) :
	_board{board}
{

}

Board *AbstractGameAction::board() const
{
	return _board;
}
