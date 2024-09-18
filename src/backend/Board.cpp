#include "Board.h"
#include "Pathway.h"
#include "Field.h"
#include "Pawn.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

Board::Board(QObject *parent) :
	QObject{parent},
	m_pathway{new Pathway(40, this)}
{
	for (int n{0}; n < 4; n++)
		m_homes.append(new Pathway(4, this));
}

QJsonObject Board::boardLayout() const
{
	QJsonObject json;
	QJsonArray pathway;
	QJsonArray homes;

    for (int n{0}; n < m_pathway->fieldCount(); n++) {
		auto *pawn = m_pathway->field(n)->pawn();

		if (pawn)
			pathway.append(QJsonObject{{"number", n},
									   {"player", pawn->playerId()}});
	}

	json["pathway"] = pathway;

    for (size_t m{0}; m < 4; m++) {
		QJsonArray home;

        for (int n{0}; n < 4; n++) {
            auto *pawn{m_homes.at(m)->field(n)->pawn()};

			if (pawn)
				home.append(QJsonObject{{"number", n},
										{"player", pawn->playerId()}});
		}

		homes.append(home);
	}

	json["homes"] = homes;

	return json;
}

bool Board::checkBringIn(int playerId) const
{
    auto *pawn{m_pathway->field(toPathwayCoordinates(0, playerId))->pawn()};

	return !pawn || pawn->playerId() != playerId;
}

QList<int> Board::findPossibleMoves(int score, int playerId) const
{
	QList<int> moves;
    int pathwayFieldCnt{m_pathway->fieldCount()};

    for (size_t fieldNum{0}; fieldNum < pathwayFieldCnt; fieldNum++) {
        auto *pawn{m_pathway->field(fieldNum)->pawn()};

		if (pawn && pawn->playerId() == playerId
			&& (pawn->traveledDistance() + score < pathwayFieldCnt
				? isMovePossible(playerId, fieldNum, score)
				: isBringOutPossible(pawn, score)))
			moves.append(fieldNum);
	}

	return moves;
}

bool Board::bringPawnIn(Pawn *pawn)
{
	if (!pawn)
		return false;

    int playerId{pawn->playerId()};

	return m_pathway->bringPawnIn(pawn, toPathwayCoordinates(0, playerId));
}

bool Board::movePawn(int playerId, int fieldNumber, int score)
{
    auto *pawn{m_pathway->field(fieldNumber)->pawn()};
    int pathwayFieldCnt{m_pathway->fieldCount()};

	if (pawn && pawn->playerId() == playerId
		&& (pawn->traveledDistance() + score < pathwayFieldCnt)) {
		if (isMovePossible(playerId, fieldNumber, score))
			return m_pathway->movePawn(fieldNumber, score);
	} else {
		if (isBringOutPossible(pawn, score))
			return takePawnOut(fieldNumber, score);
	}

	return false;
}

bool Board::takePawnOut(int fieldNumber, int score)
{
    auto *pawn{m_pathway->takePawnOut(fieldNumber)};

	if (!pawn)
		return false;

    auto *home{m_homes.at(pawn->playerId())};

	if (!home->bringPawnIn(pawn, pawn->traveledDistance() - 40 + score))
		return false;

	if (home->isFull())
		emit playerEscaped(pawn->playerId());

	return true;
}

void Board::reset()
{
	m_pathway->reset();

    for (auto *home : m_homes)
		home->reset();
}

bool Board::isBringOutPossible(Pawn *pawn, int score) const
{
	if (!pawn)
		return false;

    int fieldNum{pawn->traveledDistance() + score - m_pathway->fieldCount()};

	if (fieldNum > 3)
		return false;

	return !m_homes.at(pawn->playerId())->field(fieldNum)->pawn();
}

bool Board::isMovePossible(int playerId, int srcFieldNum, int score) const
{
    int pathwayFieldCnt{m_pathway->fieldCount()};
    int dstFieldNum{srcFieldNum + score};

	if (dstFieldNum >= pathwayFieldCnt)
		dstFieldNum -= pathwayFieldCnt;

    auto *pawn{m_pathway->field(dstFieldNum)->pawn()};

	return !pawn || pawn->playerId() != playerId;
}

int Board::toPathwayCoordinates(int fieldNumber, int playerId) const
{
	return 10*playerId + fieldNumber;
}
