#include "MainWindow.h"
#include "backend/Game.h"
#include "backend/Player.h"
#include "ScoreDisplay.h"
#include "BoardView.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_game{new Game(this)},
	m_boardView{new BoardView(this)},
	m_labelPlayer{new QLabel("Player: 0", this)},
	m_btnRollDice{new QPushButton(tr("&Roll Dice"), this)},
	m_scoreDisplay{new ScoreDisplay(this)}
{
	auto *widget = new QWidget(this);
	auto *layoutMain = new QVBoxLayout(widget);
	auto *layoutDice = new QHBoxLayout();

	m_btnRollDice->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	layoutDice->addWidget(m_scoreDisplay);
	layoutDice->addWidget(m_btnRollDice);

	layoutMain->addWidget(m_boardView);
	layoutMain->addLayout(layoutDice);
	layoutMain->addWidget(m_labelPlayer);
	layoutMain->setContentsMargins(0, 0, 0, 0);

	setCentralWidget(widget);
	resize(1000, 1000);

	connect(m_game, &Game::diceRolled, this, &MainWindow::onDiceRolled);
	connect(m_game, &Game::canBringOn, m_boardView, &BoardView::enableBringOn);
//	connect(m_game, &Game::possibleMoves, this, &MainWindow::showPossibleMoves);
//	connect(m_game, &Game::playerPawnsCountChanged, this, &MainWindow::onPlayerPawnsCountChanged);
//	connect(m_game, &Game::nextTurn, this, &MainWindow::onNextTurn);

	connect(m_btnRollDice, &QPushButton::clicked, this, &MainWindow::onRollDice);
	connect(m_boardView, &BoardView::bringOn, this, &MainWindow::onBringOn);
//	connect(ui->listMoves, &QListWidget::itemDoubleClicked, this, &MainWindow::onMoveSelected);

//	updateBoard();
}

void MainWindow::updateBoard()
{
//	const QList<QPair<int, int>> &pawns{m_game->boardLayout()};

//	for (const auto &pawn : pawns)
//		ui->listBoard->addItem(QString::number(pawn.first) + ": "
//							   + QString::number(pawn.second));
}

void MainWindow::onDiceRolled(int score)
{
	m_scoreDisplay->setText(QString::number(score));
}

void MainWindow::showPossibleMoves(const QList<int> &moves)
{
//	if (!ui->btnBringOn->isEnabled() && moves.isEmpty()) {
//		QMessageBox::warning(this, "Ludo", "You have no valid moves.");
//		m_game->advance();

//		return;
//	}

//	for (const auto &fieldNumber : moves)
//		ui->listMoves->addItem(QString::number(fieldNumber));
}

void MainWindow::onPlayerPawnsCountChanged(Player *player)
{
//	switch (player->id()) {
//	case Game::PT_Blue:
//		ui->labelHomeBlue->setText(QString::number(player->pawnsCount()));
//		break;
//	case Game::PT_Yellow:
//		ui->labelHomeYellow->setText(QString::number(player->pawnsCount()));
//		break;
//	case Game::PT_Green:
//		ui->labelHomeGreen->setText(QString::number(player->pawnsCount()));
//		break;
//	case Game::PT_Red:
//		ui->labelHomeRed->setText(QString::number(player->pawnsCount()));
//		break;
//	}
}

void MainWindow::onNextTurn(int currentPlayerId)
{
	m_labelPlayer->setText("Player: " + QString::number(currentPlayerId));
	m_btnRollDice->setEnabled(true);
	m_boardView->enableBringOn(false);
//	ui->labelDice->clear();
//	ui->listMoves->clear();
//	ui->listBoard->clear();

//	updateBoard();
}

void MainWindow::onRollDice()
{
	m_btnRollDice->setEnabled(false);
	m_game->rollDice();
}

void MainWindow::onBringOn()
{
	m_boardView->enableBringOn(false);
	m_game->bringPawnOn();
}

void MainWindow::onMoveSelected(QListWidgetItem *item)
{
	m_game->movePawn(item->text().toInt());
}
