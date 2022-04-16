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
	int pawnsCount() const;

	bool bringPawnIn(Pawn *pawn, int fieldNumber);
	bool movePawn(int fieldNumber, int fieldCount);
	Pawn *takePawnOut(int fieldNumber);
	void reset();

private:
	Pawn *pawn(int fieldNumber);
	bool occupyField(Field *field, Pawn *pawn);

	int m_pawnsCount;
	QList<Field *> m_fields;

signals:
	void pawnsCountChanged(int pawnsCount);
};

#endif // PATHWAY_H
