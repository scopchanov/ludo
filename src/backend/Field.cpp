#include "Field.h"

Field::Field(QObject *parent) :
	QObject(parent),
	_pawn{nullptr}
{

}

Pawn *Field::pawn() const
{
	return _pawn;
}

void Field::setPawn(Pawn *pawn)
{
	_pawn = pawn;
}
