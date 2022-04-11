#ifndef PATHWAY_H
#define PATHWAY_H

#include <QObject>

class Field;
class Pawn;

class Pathway : public QObject
{
	Q_OBJECT
public:
	explicit Pathway(QObject *parent = nullptr);

	Field *field(int n) const;
	int fieldCount() const;
	bool bringPawnIn(Pawn *pawn, int fieldNumber);
	bool movePawn(int srcFieldNumber, int fieldCount);
	Pawn *bringPawnOut(int fieldNumber);
	void reset();

private:
	bool occupyField(Field *field, Pawn *pawn);

	QList<Field *> m_fields;
};

#endif // PATHWAY_H
