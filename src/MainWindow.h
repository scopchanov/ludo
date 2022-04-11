#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;
class Game;
class BoardView;
class ScoreItem;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);

private:
	Game *m_game;
	BoardView *m_boardView;
	QPushButton *m_btnRollDice;
	ScoreItem *m_scoreDisplay;

private slots:
	void onDiceRolled(int score);
	void showPossibleMoves(const QList<int> &moves);
	void onNextTurn(int currentPlayerId);
	void onRollDice();
	void onPlayerWins(int playerId);
};
#endif // MAINWINDOW_H
