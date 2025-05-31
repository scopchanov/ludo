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

Path::Path(int tileCount, QObject *parent) :
	QObject{parent},
	_pawnCount{0}
{
	for (int n{0}; n < tileCount; n++)
		_tiles.append(new Tile(this));
}

Player Path::playerAt(int tileIndex) const
{
	return isValidTile(tileIndex) ? _tiles.at(tileIndex)->player() : Player{};
}

bool Path::setPlayerAt(int player, int tileIndex)
{
	if (!isValidTile(tileIndex))
		return false;

	_tiles.at(tileIndex)->occupyBy(player);
	_pawnCount++;

	return true;
}

int Path::tileCount() const
{
	return _tiles.count();
}

bool Path::isTileOccupiedBy(int player, int srcTileIndex) const
{
	Player occupant{playerAt(srcTileIndex)};

	return occupant.has_value() && occupant == player;
}

bool Path::canBringPawnIn(int player, int tileIndex)
{
	return isValidTile(tileIndex) && !isFullyOccupied()
	&& canOccupy(player, _tiles.at(tileIndex));
}

bool Path::canMove(int player, int srcTileIndex, int steps) const
{
	return isTileOccupiedBy(player, srcTileIndex)
	&& canOccupy(player, _tiles.at(wrappedIndex(srcTileIndex + steps)));
}

int Path::distance(int fromTileIndex, int toTileIndex)
{
	return (toTileIndex - fromTileIndex + _tiles.count()) % _tiles.count();
}

bool Path::bringPawnIn(int player, int tileIndex)
{
	if (!canBringPawnIn(player, tileIndex))
		return false;

	occupy(player, _tiles.at(tileIndex));

	_pawnCount++;

	if (isFullyOccupied())
		emit pathFull();

	return true;
}

bool Path::movePawn(int player, int srcTileIndex, int steps)
{
	if (!canMove(player, srcTileIndex, steps))
		return false;

	auto *srcTile{tile(srcTileIndex)};

	occupy(player, _tiles.at(wrappedIndex(srcTileIndex + steps)));

	srcTile->clear();

	return true;
}

Player Path::removePlayerAt(int tileIndex)
{
	auto *srcTile{tile(tileIndex)};
	Player player{srcTile ? srcTile->removePlayer() : Player{}};

	if (player.has_value())
		_pawnCount--;

	return player;
}

void Path::clear()
{
	for (auto *tile : std::as_const(_tiles))
		tile->clear();

	_pawnCount = 0;
}

bool Path::occupy(int player, Tile *tile)
{
	Player occupant{tile->player()};

	if (occupant.has_value()) {
		if (player == occupant)
			return false;
		else
			emit pawnBusted(occupant.value());
	}

	tile->occupyBy(player);

	return true;
}

bool Path::canOccupy(int player, Tile *tile) const
{
	Player existingPlayer{tile->player()};

	return existingPlayer.has_value() ? player != existingPlayer : true;
}

Tile *Path::tile(int index) const
{
	return isValidTile(index) ? _tiles.at(index) : nullptr;
}

bool Path::isFullyOccupied() const
{
	return _pawnCount == _tiles.count();
}

int Path::wrappedIndex(int index) const
{
	return index % _tiles.count();
}

bool Path::isValidTile(int index) const
{
	return index >= 0 && index < _tiles.count();
}
