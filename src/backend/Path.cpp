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

#include "Path.h"
#include "Tile.h"
#include "Pawn.h"

Path::Path(int tileCount, QObject *parent) :
	QObject{parent},
	_pawnsCount{0}
{
	for (int n{0}; n < tileCount; n++)
		_tiles.append(new Tile(this));
}

Pawn *Path::pawnAt(int tileNumber)
{
	return isValidTile(tileNumber) ? _tiles.at(tileNumber)->pawn() : nullptr;
}

int Path::tileCount() const
{
	return _tiles.count();
}

bool Path::isFull() const
{
	return _pawnsCount >= _tiles.count();
}

bool Path::bringPawnIn(Pawn *pawn, int tileNumber)
{
	bool canBringIn{pawn && isValidTile(tileNumber) && !isFull()
		&& occupyTile(_tiles.at(tileNumber), pawn)};

	if (canBringIn)
		_pawnsCount++;

	return canBringIn;
}

bool Path::movePawn(int srcTileNumber, int steps)
{
	auto *srcTile{tile(srcTileNumber)};
	auto *pawn{srcTile ? srcTile->pawn() : nullptr};

	if (!pawn || !occupyTile(_tiles.at(wrappedIndex(srcTileNumber + steps)), pawn))
		return false;

	pawn->addTrip(steps);
	srcTile->setPawn(nullptr);

	return true;
}

Pawn *Path::takePawn(int tileNumber)
{
	auto *srcTile{tile(tileNumber)};
	auto *pawn{srcTile ? srcTile->takePawn() : nullptr};

	if (pawn)
		_pawnsCount--;

	return pawn;
}

void Path::reset()
{
	for (auto *tile : std::as_const(_tiles))
		tile->reset();

	_pawnsCount = 0;
}

bool Path::occupyTile(Tile *tile, Pawn *pawn)
{
	auto *existingPawn{tile->pawn()};

	if (existingPawn) {
		if (existingPawn->playerId() == pawn->playerId())
			return false;
		else
			existingPawn->bust();
	}

	tile->setPawn(pawn);

	return true;
}

Tile *Path::tile(int n) const
{
	return isValidTile(n) ? _tiles.at(n) : nullptr;
}

int Path::wrappedIndex(int n) const
{
	return n % _tiles.count();
}

bool Path::isValidTile(int n) const
{
	return n >= 0 && n < _tiles.count();
}
