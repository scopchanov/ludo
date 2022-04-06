#ifndef GAME_H
#define GAME_H

#include <QObject>

class Board;
class Dice;
class Player;

class Game : public QObject
{
	Q_OBJECT
public:
	enum PlayerType : int {
		PT_Blue = 0,
		PT_Yellow,
		PT_Green,
		PT_Red
	};

	explicit Game(QObject *parent = nullptr);

	QList<QPair<int, int> > boardLayout() const;

	void rollDice();
	void bringPawnOn();
	void movePawn(int srcField);
	void advance();
	void reset();

private:
	int toBoardCoordinates(int fieldNumber) const;
	int toPlayerCoordinates(int fieldNumber) const;

	Board *m_board;
	Dice *m_dice;
	int m_currentPlayerId;
	QList<Player *> m_players;

private slots:
	void onPawnsCountChanged();

signals:
	void diceRolled(int score);
	void canBringOn(bool isBringOnPossible);
	void possibleMoves(const QList<int> &moves);
	void pawnCountChanged(int playerId, int pawnCount);
	void nextTurn(int currentPlayerId);
};

#endif // GAME_H
