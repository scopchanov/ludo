#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;
class Game;
class BoardScene;
class ScoreItem;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);

private:
	Game *m_game;
    BoardScene *m_board;
	QPushButton *m_btnRollDice;
	ScoreItem *m_scoreDisplay;

private slots:
	void onDiceRolled(int score);
	void showPossibleMoves(const QList<int> &moves);
	void onNextTurn(int currentPlayerId);
	void onRollDice();
	void onPlayerWon(int playerId);
	void onGameOver();
};
#endif // MAINWINDOW_H
