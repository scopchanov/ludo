#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;
class QListWidgetItem;
class Game;
class Player;
class BoardView;
class ScoreDisplay;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);

private:
	void updateBoard();

	Game *m_game;
	BoardView *m_boardView;
	QLabel *m_labelPlayer;
	QPushButton *m_btnRollDice;
	ScoreDisplay *m_scoreDisplay;

private slots:
	void onDiceRolled(int score);
	void showPossibleMoves(const QList<int> &moves);
	void onPlayerPawnsCountChanged(Player *player);
	void onNextTurn(int currentPlayerId);
	void onRollDice();
	void onBringOn();
	void onMoveSelected(QListWidgetItem *item);
};
#endif // MAINWINDOW_H
