#ifndef BOARD_H
#define BOARD_H

#include <QObject>

class Field;
class Pawn;

class Board : public QObject
{
	Q_OBJECT
public:
	explicit Board(QObject *parent = nullptr);

	Field *field(int n) const;
	bool bringPawnOn(Pawn *pawn, int fieldNumber);
	bool movePawn(int srcSquare, int places);
	void reset();

private:
	bool occupyField(Field *field, Pawn *pawn);

	QList<Field *> m_fields;

signals:
	void moveMade();
};

#endif // BOARD_H
