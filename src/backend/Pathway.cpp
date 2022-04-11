#include "Pathway.h"
#include "Field.h"
#include "Pawn.h"
#include <QDebug>

Pathway::Pathway(QObject *parent) :
	QObject{parent}
{
	for (int n = 0; n < 40; n++)
		m_fields.append(new Field(this));
}

Field *Pathway::field(int n) const
{
	if (n < 0 || n >= m_fields.count())
		return nullptr;

	return m_fields.at(n);
}

int Pathway::fieldCount() const
{
	return m_fields.count();
}

bool Pathway::bringPawnIn(Pawn *pawn, int fieldNumber)
{
	return occupyField(m_fields.at(fieldNumber), pawn);
}

bool Pathway::movePawn(int srcFieldNumber, int fieldCount)
{
	if (srcFieldNumber < 0 || srcFieldNumber >= m_fields.count())
		return false;

	auto *pawn = m_fields.at(srcFieldNumber)->pawn();

	if (!pawn)
		return false;

	int dstFieldNumber = srcFieldNumber + fieldCount;

	if (dstFieldNumber >= m_fields.count())
		dstFieldNumber -= m_fields.count();

	if (!occupyField(m_fields.at(dstFieldNumber), pawn))
		return false;

	pawn->increaseTraveledDistance(fieldCount);

	m_fields.at(srcFieldNumber)->setPawn(nullptr);

	return true;
}

Pawn *Pathway::bringPawnOut(int fieldNumber)
{
	if (fieldNumber < 0 || fieldNumber >= m_fields.count())
		return nullptr;

	auto *field = m_fields.at(fieldNumber);
	auto *pawn = field->pawn();

	field->setPawn(nullptr);

	return pawn;
}

void Pathway::reset()
{

}

bool Pathway::occupyField(Field *field, Pawn *pawn)
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
