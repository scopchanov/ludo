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

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

class QPushButton;
class BoardScene;
class DiceItem;
class Game;

class GameWidget : public QWidget
{
	Q_OBJECT
public:
	explicit GameWidget(QWidget *parent = nullptr);

	void startNewGame(const QString &filename);
	void loadGame(const QString &filename);

private:
	void showActions();

	Game *_game;
	BoardScene *_board;
	QPushButton *_btnRollDice;
	DiceItem *_scoreDisplay;
	QString _filename;

private slots:
	void onDiceRolled(int score);
	void onStateChanged();
	void onNextTurn(int currentPlayerId);
	void onRollDice();

signals:
	void playerWon(int playerId);
	void gameOver();
};

#endif // GAMEWIDGET_H
