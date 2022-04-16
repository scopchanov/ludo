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
	QList<int> findPossibleMoves(int score, int playerId) const;

	bool bringPawnIn(Pawn *pawn);
	bool movePawn(int playerId, int fieldNumber, int score);
	bool takePawnOut(int fieldNumber, int score);
	void reset();

private:
	bool checkBringOut(Pawn *pawn, int score) const;
	bool checkMove(int playerId, int srcFieldNum, int score) const;
	int toPathwayCoordinates(int fieldNumber, int playerId) const;

	Pathway *m_pathway;
	QList<Pathway *> m_homes;

private slots:
	void onFullHome();

signals:
	void playerWins(int playerId);
};

#endif // BOARD_H
