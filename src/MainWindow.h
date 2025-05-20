#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;
class BoardScene;
class ScoreItem;
class Game;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);

private:
	Game *_game;
	BoardScene *_board;
	QPushButton *_btnRollDice;
	ScoreItem *_scoreDisplay;

private slots:
	void onDiceRolled(int score);
	void showPossibleMoves(const QList<int> &moves);
	void onNextTurn(int currentPlayerId);
	void onRollDice();
	void onPlayerWon(int playerId);
	void onGameOver();
};
#endif // MAINWINDOW_H
