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
