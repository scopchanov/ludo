#include "Pathway.h"
#include "Field.h"
#include "Pawn.h"

Pathway::Pathway(int fieldCount, QObject *parent) :
	QObject{parent},
	m_pawnsCount{0}
{
	for (int n{0}; n < fieldCount; n++)
		m_fields.append(new Field(this));
}

Field *Pathway::field(int n) const
{
	return isFieldIndexValid(n) ? m_fields.at(n) : nullptr;
}

int Pathway::fieldCount() const
{
	return m_fields.count();
}

bool Pathway::isFull() const
{
	return m_pawnsCount >= m_fields.count();
}

bool Pathway::bringPawnIn(Pawn *pawn, int fieldNumber)
{
    bool success{!isFull() && pawn && isFieldIndexValid(fieldNumber)
        && occupyField(m_fields.at(fieldNumber), pawn)};

	m_pawnsCount += success;

	return success;
}

bool Pathway::movePawn(int fieldNumber, int fieldCount)
{
    auto *field{Pathway::field(fieldNumber)};

	if (!field || !field->pawn())
		return false;

    auto *pawn{field->pawn()};
    int dstFieldNumber{fieldNumber + fieldCount};

	if (dstFieldNumber >= m_fields.count())
		dstFieldNumber -= m_fields.count();

	if (!occupyField(m_fields.at(dstFieldNumber), pawn))
		return false;

	pawn->increaseTraveledDistance(fieldCount);
	field->setPawn(nullptr);

	return true;
}

Pawn *Pathway::takePawnOut(int fieldNumber)
{
    auto *field{Pathway::field(fieldNumber)};
    auto *pawn{field && field->pawn() ? field->pawn() : nullptr};

	if (pawn) {
		m_fields.at(fieldNumber)->setPawn(nullptr);
		m_pawnsCount--;
	}

	return pawn;
}

void Pathway::reset()
{
    for (auto *field : m_fields)
		if (field->pawn())
			field->pawn()->deleteLater();

	m_pawnsCount = 0;
}

bool Pathway::isFieldIndexValid(int fieldNumber) const
{
	return fieldNumber >= 0 && fieldNumber < m_fields.count();
}

bool Pathway::occupyField(Field *field, Pawn *pawn)
{
    auto *existingPawn{field->pawn()};

	if (existingPawn) {
		if (existingPawn->playerId() == pawn->playerId())
			return false;
		else
			existingPawn->bust();
	}

	field->setPawn(pawn);

	return true;
}
