#include "MainWindow.h"
#include "backend/Game.h"
#include "backend/Player.h"
#include "frontend/ScoreItem.h"
#include "frontend/BoardView.h"
#include "frontend/BoardScene.h"
#include <QJsonObject>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_game{new Game(this)},
	m_boardView{new BoardView(this)},
	m_btnRollDice{new QPushButton(tr("&Roll Dice"), this)}
{
	auto *widget = new QWidget(this);
	auto *layoutMain = new QHBoxLayout(widget);

	m_btnRollDice->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

	layoutMain->addWidget(m_boardView);
	layoutMain->addWidget(m_btnRollDice);
	layoutMain->setContentsMargins(0, 0, 0, 0);

	setCentralWidget(widget);
	resize(1200, 1000);

	connect(m_game, &Game::diceRolled, this, &MainWindow::onDiceRolled);
	connect(m_game, &Game::bringInChanged, m_boardView->board(), &BoardScene::enableBringIn);
	connect(m_game, &Game::possibleMoves, this, &MainWindow::showPossibleMoves);
	connect(m_game, &Game::pawnCountChanged, m_boardView->board(), &BoardScene::changePawnCount);
	connect(m_game, &Game::nextTurn, this, &MainWindow::onNextTurn);
	connect(m_game, &Game::playerWins, this, &MainWindow::onPlayerWins);

	connect(m_btnRollDice, &QPushButton::clicked, this, &MainWindow::onRollDice);
	connect(m_boardView, &BoardView::bringPawnIn, m_game, &Game::bringPawnIn);
	connect(m_boardView, &BoardView::movePawn, m_game, &Game::movePawn);
}

void MainWindow::onDiceRolled(int score)
{
	m_boardView->board()->setScore(score);
}

void MainWindow::showPossibleMoves(const QList<int> &moves)
{
	if (m_boardView->board()->canBringIn() || !moves.isEmpty()) {
		m_boardView->board()->highlightFields(moves);
	} else {
		QMessageBox::warning(this, "Ludo", "You have no valid moves.");
		m_game->advance();
	}
}

void MainWindow::onNextTurn(int currentPlayerId)
{
	m_btnRollDice->setEnabled(true);
	m_boardView->board()->enableBringIn(false);
	m_boardView->board()->setScore(0);
	m_boardView->board()->setCurrentPlayerId(currentPlayerId);
	m_boardView->board()->clearHighlight();
	m_boardView->board()->updateBoard(m_game->boardLayout());
}

void MainWindow::onRollDice()
{
	m_btnRollDice->setEnabled(false);
	m_game->rollDice();
}

void MainWindow::onPlayerWins(int playerId)
{
	QMessageBox::information(this, "Ludo", "Player " + QString::number(playerId)
							 + " wins.");

	m_game->reset();
}
