#ifndef FIELD_H
#define FIELD_H

#include <QObject>

class Pawn;

class Field : public QObject
{
	Q_OBJECT
public:
	explicit Field(QObject *parent = nullptr);

	Pawn *pawn() const;
	void setPawn(Pawn *pawn);

private:
	Pawn *_pawn;
};

#endif // FIELD_H
