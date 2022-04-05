#include "Field.h"

Field::Field(QObject *parent) :
	QObject(parent),
	m_pawn{nullptr}
{

}

Pawn *Field::pawn() const
{
	return m_pawn;
}

void Field::setPawn(Pawn *pawn)
{
	m_pawn = pawn;
}
