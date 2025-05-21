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

#ifndef PATHWAY_H
#define PATHWAY_H

#include <QObject>

class Field;
class Pawn;

class Pathway : public QObject
{
	Q_OBJECT
public:
	explicit Pathway(int fieldCount, QObject *parent = nullptr);

	Field *field(int n) const;
	int fieldCount() const;
	bool isFull() const;

	bool bringPawnIn(Pawn *pawn, int fieldNumber);
	bool movePawn(int fieldNumber, int fieldCount);
	Pawn *takePawnOut(int fieldNumber);
	void reset();

private:
	bool isFieldIndexValid(int fieldNumber) const;
	bool occupyField(Field *field, Pawn *pawn);

	int _pawnsCount;
	QList<Field *> _fields;
};

#endif // PATHWAY_H
