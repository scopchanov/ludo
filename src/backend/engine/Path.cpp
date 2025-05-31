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
#include "Pawn.h"
#include "Tile.h"

Path::Path(int tileCount, QObject *parent) :
	QObject{parent},
	_pawnCount{0}
{
	for (int n{0}; n < tileCount; n++)
		_tiles.append(new Tile(this));
}

Pawn *Path::pawnAt(int tileIndex) const
{
	return isValidTile(tileIndex) ? _tiles.at(tileIndex)->pawn() : nullptr;
}

bool Path::putPawnBackAt(Pawn *pawn, int tileIndex)
{
	if (!isValidTile(tileIndex))
		return false;

	_tiles.at(tileIndex)->setPawn(pawn);
	_pawnCount++;

	return true;
}

Tile *Path::tile(int n) const
{
	return isValidTile(n) ? _tiles.at(n) : nullptr;
}

int Path::tileCount() const
{
	return _tiles.count();
}

bool Path::canBringPawnIn(Pawn *pawn, int tileIndex)
{
	return pawn && isValidTile(tileIndex) && !isFullyOccupied()
	&& canOccupy(pawn, _tiles.at(tileIndex));
}

bool Path::canMove(int playerId, int srcTileIndex, int steps) const
{
	auto *pawn{pawnAt(srcTileIndex)};

	return pawn && pawn->playerId() == playerId
		   && canOccupy(pawn, _tiles.at(wrappedIndex(srcTileIndex + steps)));
}

int Path::distance(int fromTileIndex, int toTileIndex)
{
	return (toTileIndex - fromTileIndex + _tiles.count()) % _tiles.count();
}

bool Path::bringPawnIn(Pawn *pawn, int tileIndex)
{
	if (!canBringPawnIn(pawn, tileIndex))
		return false;

	occupy(pawn, _tiles.at(tileIndex));

	_pawnCount++;

	return true;
}

bool Path::movePawn(int playerId, int srcTileIndex, int steps)
{
	if (!canMove(playerId, srcTileIndex, steps))
		return false;

	auto *srcTile{tile(srcTileIndex)};
	auto *pawn{srcTile->pawn()};

	occupy(pawn, _tiles.at(wrappedIndex(srcTileIndex + steps)));

	srcTile->setPawn(nullptr);

	return true;
}

Pawn *Path::takePawn(int tileIndex)
{
	auto *srcTile{tile(tileIndex)};
	auto *pawn{srcTile ? srcTile->takePawn() : nullptr};

	if (pawn)
		_pawnCount--;

	return pawn;
}

void Path::reset()
{
	for (auto *tile : std::as_const(_tiles))
		tile->reset();

	_pawnCount = 0;
}

bool Path::occupy(Pawn *pawn, Tile *tile)
{
	auto *existingPawn{tile->pawn()};

	if (existingPawn) {
		if (existingPawn->playerId() == pawn->playerId())
			return false;
		else
            emit pawnBusted(existingPawn);
	}

	tile->setPawn(pawn);

	return true;
}

bool Path::canOccupy(Pawn *pawn, Tile *tile) const
{
	auto *existingPawn{tile->pawn()};

	return existingPawn ? existingPawn->playerId() != pawn->playerId() : true;
}

bool Path::isFullyOccupied() const
{
	return _pawnCount >= _tiles.count();
}

int Path::wrappedIndex(int index) const
{
	return index % _tiles.count();
}

bool Path::isValidTile(int index) const
{
	return index >= 0 && index < _tiles.count();
}
