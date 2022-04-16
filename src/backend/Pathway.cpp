#include "Pathway.h"
#include "Field.h"
#include "Pawn.h"

Pathway::Pathway(int fieldCount, QObject *parent) :
	QObject{parent},
	m_pawnsCount{0}
{
	for (int n = 0; n < fieldCount; n++)
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

int Pathway::pawnsCount() const
{
	return m_pawnsCount;
}

bool Pathway::bringPawnIn(Pawn *pawn, int fieldNumber)
{
	if (!pawn || fieldNumber < 0 || fieldNumber > m_fields.count())
		return false;

	if (!occupyField(m_fields.at(fieldNumber), pawn))
		return false;

	emit pawnsCountChanged(++m_pawnsCount);

	return true;
}

bool Pathway::movePawn(int fieldNumber, int fieldCount)
{
	auto *field = Pathway::field(fieldNumber);

	if (!field || !field->pawn())
		return false;

	auto *pawn = field->pawn();
	int dstFieldNumber = fieldNumber + fieldCount;

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
	auto *pawn = Pathway::pawn(fieldNumber);

	if (pawn) {
		m_fields.at(fieldNumber)->setPawn(nullptr);
		emit pawnsCountChanged(--m_pawnsCount);
	}

	return pawn;
}

void Pathway::reset()
{
	for (auto *field : qAsConst(m_fields)) {
		auto *pawn = field->pawn();

		if (pawn)
			pawn->deleteLater();
	}

	m_pawnsCount = 0;

	emit pawnsCountChanged(m_pawnsCount);
}

Pawn *Pathway::pawn(int fieldNumber)
{
	auto *field = Pathway::field(fieldNumber);

	if (!field || !field->pawn())
		return nullptr;

	return field->pawn();
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
