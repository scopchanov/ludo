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

#ifndef BOARD_H
#define BOARD_H

#include <QObject>

class Pathway;
class Pawn;

class Board : public QObject
{
	Q_OBJECT
public:
	explicit Board(QObject *parent = nullptr);

	QJsonObject boardLayout() const;
	bool checkBringIn(int playerId) const;
	QList<int> findPossibleMoves(int playerId, int score) const;

	bool bringPawnIn(Pawn *pawn);
	bool movePawn(int playerId, int fieldNumber, int score);
	bool takePawnOut(int fieldNumber, int score);
	void reset();

private:
	bool isBringOutPossible(Pawn *pawn, int score) const;
	bool isMovePossible(int playerId, int srcFieldNum, int score) const;
	int toPathwayCoordinates(int fieldNumber, int playerId) const;
	int wrappedIndex(int index, int length);

	Pathway *_pathway;
	QList<Pathway *> _homes;

signals:
	void playerEscaped(int playerId);
};

#endif // BOARD_H
