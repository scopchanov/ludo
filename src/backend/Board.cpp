/**
MIT License

Copyright (c) 2022-2025 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Board.h"
#include "Pathway.h"
#include "Field.h"
#include "Pawn.h"
#include <QJsonObject>
#include <QJsonArray>

Board::Board(QObject *parent) :
	QObject{parent},
	_pathway{new Pathway(40, this)}
{
	for (int n{0}; n < 4; n++)
		_homes.append(new Pathway(4, this));
}

QJsonObject Board::boardLayout() const
{
	QJsonObject json;
	QJsonArray pathway;
	QJsonArray homes;

    for (int n{0}; n < _pathway->fieldCount(); n++) {
		auto *pawn = _pathway->field(n)->pawn();

		if (pawn)
			pathway.append(QJsonObject{{"number", n},
									   {"player", pawn->playerId()}});
	}

	json["pathway"] = pathway;

    for (size_t m{0}; m < 4; m++) {
		QJsonArray home;

        for (int n{0}; n < 4; n++) {
            auto *pawn{_homes.at(m)->field(n)->pawn()};

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
    auto *pawn{_pathway->field(toPathwayCoordinates(0, playerId))->pawn()};

	return !pawn || pawn->playerId() != playerId;
}

QList<int> Board::findPossibleMoves(int score, int playerId) const
{
	QList<int> moves;
    int pathwayFieldCnt{_pathway->fieldCount()};

	for (int fieldNum{0}; fieldNum < pathwayFieldCnt; fieldNum++) {
        auto *pawn{_pathway->field(fieldNum)->pawn()};

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

	return _pathway->bringPawnIn(pawn, toPathwayCoordinates(0, playerId));
}

bool Board::movePawn(int playerId, int fieldNumber, int score)
{
    auto *pawn{_pathway->field(fieldNumber)->pawn()};
    int pathwayFieldCnt{_pathway->fieldCount()};

	if (pawn && pawn->playerId() == playerId
		&& (pawn->traveledDistance() + score < pathwayFieldCnt)) {
		if (isMovePossible(playerId, fieldNumber, score))
			return _pathway->movePawn(fieldNumber, score);
	} else {
		if (isBringOutPossible(pawn, score))
			return takePawnOut(fieldNumber, score);
	}

	return false;
}

bool Board::takePawnOut(int fieldNumber, int score)
{
    auto *pawn{_pathway->takePawnOut(fieldNumber)};

	if (!pawn)
		return false;

    auto *home{_homes.at(pawn->playerId())};

	if (!home->bringPawnIn(pawn, pawn->traveledDistance() - 40 + score))
		return false;

	if (home->isFull())
		emit playerEscaped(pawn->playerId());

	return true;
}

void Board::reset()
{
	_pathway->reset();

	for (auto *home : std::as_const(_homes))
		home->reset();
}

bool Board::isBringOutPossible(Pawn *pawn, int score) const
{
	if (!pawn)
		return false;

    int fieldNum{pawn->traveledDistance() + score - _pathway->fieldCount()};

	if (fieldNum > 3)
		return false;

	return !_homes.at(pawn->playerId())->field(fieldNum)->pawn();
}

bool Board::isMovePossible(int playerId, int srcFieldNum, int score) const
{
    int pathwayFieldCnt{_pathway->fieldCount()};
    int dstFieldNum{srcFieldNum + score};

	if (dstFieldNum >= pathwayFieldCnt)
		dstFieldNum -= pathwayFieldCnt;

    auto *pawn{_pathway->field(dstFieldNum)->pawn()};

	return !pawn || pawn->playerId() != playerId;
}

int Board::toPathwayCoordinates(int fieldNumber, int playerId) const
{
	return 10*playerId + fieldNumber;
}
