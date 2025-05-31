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
class Dice;

class Game : public QObject
{
	Q_OBJECT
public:
	explicit Game(QObject *parent = nullptr);

	QJsonObject state() const;
	void setState(const QJsonObject &json);
	int currentplayer() const;
	bool canBringIn() const;
	QList<int> possibleMoves() const;

	void init();
	void reset();
	void rollDice();
	void bringPawnIn();
	void movePawn(int srcTileIndex);

private:
	void advance();
	void switchToNextPlayer();

	Dice *_dice;
	Board *_board;
	int _playerCount;
	int _currentplayer;
	QList<int> _winners;

private slots:
	void onPlayerEscaped(int player);

signals:
	void stateChanged();
	void diceRolled(int score);
	void nextTurn(int player);
	void playerEscaped(int player);
	void gameOver();
};

#endif // GAME_H
