#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Pawn;

class Player : public QObject
{
	Q_OBJECT
public:
	explicit Player(int playerId, QObject *parent = nullptr);

	int id() const;
	int pawnsCount() const;
	Pawn *takePawn();
	void reset();

private:
	int _id;
	QList<Pawn *> _pawns;

private slots:
	void onPawnBusted();

signals:
	void pawnsCountChanged();
};

#endif // PLAYER_H
