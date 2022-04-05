#include "Board.h"
#include "Field.h"
#include "Pawn.h"
#include <QDebug>

Board::Board(QObject *parent) :
	QObject{parent}
{
	for (int n = 0; n < 40; n++)
		m_fields.append(new Field(this));
}

Field *Board::field(int n) const
{
	if (n < 0 || n >= m_fields.count())
		return nullptr;

	return m_fields.at(n);
}

bool Board::bringPawnOn(Pawn *pawn, int fieldNumber)
{
	if (!occupyField(m_fields.at(fieldNumber), pawn))
		return false;

	emit moveMade();

	return true;
}

bool Board::movePawn(int srcSquare, int places)
{
	if (srcSquare < 0)
		return false;

	auto *pawn = m_fields.at(srcSquare)->pawn();

	if (!pawn)
		return false;

	int dstSquare = srcSquare + places;

	if (dstSquare > 39)
		dstSquare -= 40;

	int totalDistance = srcSquare - 10*pawn->playerId();

	if (totalDistance < 0)
		totalDistance += 40;

	if (!(40 - totalDistance))
		qDebug() << pawn->playerId() << "is out";

	if (!occupyField(m_fields.at(dstSquare), pawn))
		return false;

	m_fields.at(srcSquare)->setPawn(nullptr);

	emit moveMade();

	return true;
}

void Board::reset()
{

}

bool Board::occupyField(Field *field, Pawn *pawn)
{
	auto *existingPawn = field->pawn();

	if (existingPawn) {
		if (existingPawn->playerId() == pawn->playerId())
			return false;
		else
			existingPawn->bust();
	}

	field->setPawn(pawn);

	return true;
}
