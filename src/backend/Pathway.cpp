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

#include "Pathway.h"
#include "Field.h"
#include "Pawn.h"

Pathway::Pathway(int fieldCount, QObject *parent) :
	QObject{parent},
	_pawnsCount{0}
{
	for (int n{0}; n < fieldCount; n++)
		_fields.append(new Field(this));
}

Field *Pathway::field(int n) const
{
	return isFieldIndexValid(n) ? _fields.at(n) : nullptr;
}

int Pathway::fieldCount() const
{
	return _fields.count();
}

bool Pathway::isFull() const
{
	return _pawnsCount >= _fields.count();
}

bool Pathway::bringPawnIn(Pawn *pawn, int fieldNumber)
{
    bool success{!isFull() && pawn && isFieldIndexValid(fieldNumber)
        && occupyField(_fields.at(fieldNumber), pawn)};

	if (success)
		_pawnsCount++;

	return success;
}

bool Pathway::movePawn(int fieldNumber, int fieldCount)
{
    auto *field{Pathway::field(fieldNumber)};

	if (!field || !field->pawn())
		return false;

    auto *pawn{field->pawn()};
    int dstFieldNumber{fieldNumber + fieldCount};

	if (dstFieldNumber >= _fields.count())
		dstFieldNumber -= _fields.count();

	if (!occupyField(_fields.at(dstFieldNumber), pawn))
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
		_fields.at(fieldNumber)->setPawn(nullptr);
		_pawnsCount--;
	}

	return pawn;
}

void Pathway::reset()
{
	for (auto *field : std::as_const(_fields))
		if (field->pawn())
			field->pawn()->deleteLater();

	_pawnsCount = 0;
}

bool Pathway::isFieldIndexValid(int fieldNumber) const
{
	return fieldNumber >= 0 && fieldNumber < _fields.count();
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
