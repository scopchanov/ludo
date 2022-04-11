#ifndef HOME_H
#define HOME_H

#include <QObject>

class Field;
class Pawn;

class Home : public QObject
{
	Q_OBJECT
public:
	explicit Home(QObject *parent = nullptr);

	int playerId() const;
	void setPlayerId(int playerId);
	Field *field(int n) const;
	bool bringPawnIn(Pawn *pawn, int fieldNumber);
	bool movePawn(int srcFieldNumber, int fieldCount);
	void reset();

private:
	bool checkAllOccupied();
	bool occupyField(Field *field, Pawn *pawn);

	int m_playerId;
	QList<Field *> m_fields;

signals:
	void fullHome();
};

#endif // HOME_H
