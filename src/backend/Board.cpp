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
	for (int n = 0; n < 4; n++) {
		auto *home = new Pathway(4, this);

		m_homes.append(home);

		connect(home, &Pathway::pawnsCountChanged, this, &Board::onFullHome);
	}
}

QJsonObject Board::boardLayout() const
{
	QJsonObject json;
	QJsonArray pathway;
	QJsonArray homes;

	for (int n = 0; n < m_pathway->fieldCount(); n++) {
		auto *pawn = m_pathway->field(n)->pawn();

		if (pawn)
			pathway.append(QJsonObject{{"number", n},
									   {"player", pawn->playerId()}});
	}

	json["pathway"] = pathway;

	for (int m = 0; m < 4; m++) {
		QJsonArray home;

		for (int n = 0; n < 4; n++) {
			auto *pawn = m_homes.at(m)->field(n)->pawn();

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
	auto *pawn = m_pathway->field(toPathwayCoordinates(0, playerId))->pawn();

	return !pawn || pawn->playerId() != playerId;
}

QList<int> Board::findPossibleMoves(int score, int playerId) const
{
	QList<int> moves;
	int pathwayFieldCnt = m_pathway->fieldCount();

	for (int fieldNum = 0; fieldNum < pathwayFieldCnt; fieldNum++) {
		auto *pawn = m_pathway->field(fieldNum)->pawn();

		if (pawn && pawn->playerId() == playerId
			&& (pawn->traveledDistance() + score < pathwayFieldCnt
				? checkMove(playerId, fieldNum, score)
				: checkBringOut(pawn, score)))
			moves.append(fieldNum);
	}

	return moves;
}

bool Board::bringPawnIn(Pawn *pawn)
{
	if (!pawn)
		return false;

	int playerId = pawn->playerId();

	return m_pathway->bringPawnIn(pawn, toPathwayCoordinates(0, playerId));
}

bool Board::movePawn(int playerId, int fieldNumber, int score)
{
	auto *pawn = m_pathway->field(fieldNumber)->pawn();
	int pathwayFieldCnt = m_pathway->fieldCount();

	if (pawn && pawn->playerId() == playerId && (pawn->traveledDistance()
												 + score < pathwayFieldCnt)) {
		if (checkMove(playerId, fieldNumber, score))
			return m_pathway->movePawn(fieldNumber, score);
	} else {
		if (checkBringOut(pawn, score))
			return takePawnOut(fieldNumber, score);
	}

	return false;
}

bool Board::takePawnOut(int fieldNumber, int score)
{
	auto *pawn = m_pathway->takePawnOut(fieldNumber);

	if (!pawn)
		return false;

	return m_homes.at(pawn->playerId())->bringPawnIn(pawn,
													 pawn->traveledDistance()
													 - 40 + score);
}

void Board::reset()
{
	m_pathway->reset();

	for (auto *home : qAsConst(m_homes))
		home->reset();
}

bool Board::checkBringOut(Pawn *pawn, int score) const
{
	if (!pawn)
		return false;

	int fieldNum = pawn->traveledDistance() + score - m_pathway->fieldCount();

	if (fieldNum > 3)
		return false;

	return !m_homes.at(pawn->playerId())->field(fieldNum)->pawn();
}

bool Board::checkMove(int playerId, int srcFieldNum, int score) const
{
	int pathwayFieldCnt = m_pathway->fieldCount();
	int dstFieldNum = srcFieldNum + score;

	if (dstFieldNum >= pathwayFieldCnt)
		dstFieldNum -= pathwayFieldCnt;

	auto *pawn = m_pathway->field(dstFieldNum)->pawn();

	return !pawn || pawn->playerId() != playerId;
}

int Board::toPathwayCoordinates(int fieldNumber, int playerId) const
{
	return 10*playerId + fieldNumber;
}

void Board::onFullHome()
{
	emit playerWins(m_homes.indexOf(static_cast<Pathway *>(sender())));
}
