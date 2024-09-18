#include "MainWindow.h"
#include "backend/Game.h"
#include "frontend/BoardView.h"
#include "frontend/BoardScene.h"
#include <QJsonObject>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_game{new Game(this)},
    m_board{nullptr},
	m_btnRollDice{new QPushButton(tr("&Roll Dice"), this)}
{
    auto *widget{new QWidget(this)};
    auto *layoutMain{new QVBoxLayout(widget)};
    auto *boardView{new BoardView(this)};

    m_board = boardView->board();

    m_btnRollDice->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_btnRollDice->setMinimumHeight(100);

    layoutMain->addWidget(boardView);
	layoutMain->addWidget(m_btnRollDice);
	layoutMain->setContentsMargins(0, 0, 0, 0);
    layoutMain->setSpacing(0);

	setCentralWidget(widget);
    resize(600, 700);

	connect(m_game, &Game::diceRolled, this, &MainWindow::onDiceRolled);
    connect(m_game, &Game::bringInChanged, m_board, &BoardScene::enableBringIn);
	connect(m_game, &Game::possibleMoves, this, &MainWindow::showPossibleMoves);
    connect(m_game, &Game::pawnCountChanged, m_board, &BoardScene::changePawnCount);
	connect(m_game, &Game::nextTurn, this, &MainWindow::onNextTurn);
	connect(m_game, &Game::playerWon, this, &MainWindow::onPlayerWon);
	connect(m_game, &Game::gameOver, this, &MainWindow::onGameOver);

	connect(m_btnRollDice, &QPushButton::clicked, this, &MainWindow::onRollDice);
    connect(boardView, &BoardView::bringPawnIn, m_game, &Game::bringPawnIn);
    connect(boardView, &BoardView::movePawn, m_game, &Game::movePawn);
}

void MainWindow::onDiceRolled(int score)
{
    m_board->setScore(score);
}

void MainWindow::showPossibleMoves(const QList<int> &moves)
{
    if (m_board->canBringIn() || !moves.isEmpty()) {
        m_board->highlightFields(moves);
	} else {
        m_board->setCurrentPlayerText(tr("Can't move."));
        // QMessageBox::warning(this, "Ludo", "You have no valid moves.");
		m_game->advance();
	}
}

void MainWindow::onNextTurn(int currentPlayerId)
{
    // m_messageView->clear();
	m_btnRollDice->setEnabled(true);
    m_board->enableBringIn(false);
    // m_board->setScore(0);
    m_board->setCurrentPlayerId(currentPlayerId);
    m_board->clearHighlight();
    m_board->updateBoard(m_game->boardLayout());
}

void MainWindow::onRollDice()
{
	m_btnRollDice->setEnabled(false);
	m_game->rollDice();
}

void MainWindow::onPlayerWon(int playerId)
{
	QMessageBox::information(this, "Ludo", "Player " + QString::number(playerId)
							 + " wins.");
}

void MainWindow::onGameOver()
{
	QMessageBox::information(this, "Ludo", "Game over.");
//	m_game->reset();
}
