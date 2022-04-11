#include "Home.h"
#include "Field.h"
#include "Pawn.h"
#include "qdebug.h"

Home::Home(QObject *parent) :
	QObject{parent},
	m_playerId{0}
{
	for (int n = 0; n < 4; n++)
		m_fields.append(new Field(this));
}

int Home::playerId() const
{
	return m_playerId;
}

void Home::setPlayerId(int playerId)
{
	m_playerId = playerId;
}

Field *Home::field(int n) const
{
	if (n < 0 || n >= m_fields.count())
		return nullptr;

	return m_fields.at(n);
}

bool Home::bringPawnIn(Pawn *pawn, int fieldNumber)
{
	if (!pawn || pawn->playerId() != m_playerId
		|| !occupyField(m_fields.at(fieldNumber), pawn))
		return false;

	if (checkAllOccupied())
		emit fullHome();

	return true;
}

bool Home::movePawn(int srcFieldNumber, int fieldCount)
{
	if (srcFieldNumber < 0 || srcFieldNumber >= m_fields.count())
		return false;

	auto *pawn = m_fields.at(srcFieldNumber)->pawn();

	if (!pawn)
		return false;

	int dstFieldNumber = srcFieldNumber + fieldCount;

	if (dstFieldNumber > m_fields.count())
		return false;

	if (!occupyField(m_fields.at(dstFieldNumber), pawn))
		return false;

	m_fields.at(srcFieldNumber)->setPawn(nullptr);

	return true;
}

void Home::reset()
{

}

bool Home::checkAllOccupied()
{
	int freeFields = m_fields.count();

	for (auto *field : qAsConst(m_fields))
		if (field->pawn())
			freeFields--;

	qDebug() << "test" << freeFields;

	return (!freeFields);
}

bool Home::occupyField(Field *field, Pawn *pawn)
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
