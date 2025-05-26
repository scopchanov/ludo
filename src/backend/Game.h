/**
MIT License

Copyright (c) 2022-2025 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
	void switchToNextPlayer();
	bool canBringIn() const;

	Board *_board;
	Dice *_dice;
	int _currentPlayerId;
	QList<Player *> _players;
	QList<Player *> _escapedPlayers;

private slots:
	void onPawnsCountChanged();
	void onPlayerEscaped(int playerId);

signals:
	void diceRolled(int score);
	void bringInChanged(bool isBringInPossible);
	void possibleMoves(const QList<int> &moves);
	void pawnCountChanged(int playerId, int pawnCount);
	void nextTurn(int currentPlayerId);
	void playerWon(int playerId);
	void gameOver();
};

#endif // GAME_H
