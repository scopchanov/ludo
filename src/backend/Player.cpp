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

#include "Player.h"
#include "Pawn.h"

Player::Player(int playerId, QObject *parent) :
	QObject{parent},
	_id{playerId}
{
	for (int n{0}; n < 4; n++) {
        auto *pawn{new Pawn(playerId, this)};

		_pawns.append(pawn);

		connect(pawn, &Pawn::busted, this, &Player::onPawnBusted);
	}
}

int Player::id() const
{
	return _id;
}

Pawn *Player::pawn(int n) const
{
	if (_pawns.isEmpty())
		return nullptr;

	return n >= 0 && n < _pawns.count() ? _pawns.at(n) : nullptr;
}

int Player::pawnsCount() const
{
	return _pawns.count();
}

Pawn *Player::takePawn()
{
	if (_pawns.isEmpty())
		return nullptr;

	auto *pawn = _pawns.takeLast();

	emit pawnsCountChanged();

	return pawn;
}

void Player::reset()
{

}

void Player::onPawnBusted()
{
	qDebug("saram rasam");
	_pawns.append(static_cast<Pawn *>(sender()));

	emit pawnsCountChanged();
}
