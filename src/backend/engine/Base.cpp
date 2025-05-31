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

#include "Base.h"
#include "Pawn.h"

Base::Base(QObject *parent) :
	QObject{parent}
{

}

void Base::addPawn(Pawn *pawn)
{
	_pawns.push(pawn);
}

int Base::pawnsCount() const
{
	return _pawns.count();
}

Pawn *Base::pawn() const
{
	return _pawns.isEmpty() ? nullptr : _pawns.top();
}

Pawn *Base::takePawn()
{
	return _pawns.isEmpty() ? nullptr : _pawns.pop();
}

void Base::reset()
{
	while(!_pawns.isEmpty())
		_pawns.pop()->reset();
}
