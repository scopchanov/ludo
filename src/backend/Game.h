#ifndef GAME_H
#define GAME_H

#include <QObject>

class Board;
class Player;
class Dice;

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

	QJsonObject boardLayout() const;

	void rollDice();
	void bringPawnIn();
	void movePawn(int srcField);
	void advance();
	void reset();

private:	
	Board *m_board;
	Dice *m_dice;
	int m_currentPlayerId;
	QList<Player *> m_players;

private slots:
	void onPawnsCountChanged();

signals:
	void diceRolled(int score);
	void bringInChanged(bool isBringInPossible);
	void possibleMoves(const QList<int> &moves);
	void pawnCountChanged(int playerId, int pawnCount);
	void nextTurn(int currentPlayerId);
	void playerWins(int playerId);
};

#endif // GAME_H
