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

#include "GameWidget.h"
#include "MainWindow.h"
#include "backend/Game.h"
#include "frontend/BoardView.h"
#include "frontend/BoardScene.h"
#include <QJsonObject>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>

GameWidget::GameWidget(QWidget *parent) :
	QWidget{parent},
	_game{new Game(this)},
	_board{new BoardScene(this)},
	_btnRollDice{new QPushButton(tr("&Roll Dice"), this)}
{
	auto *layoutMain{new QVBoxLayout(this)};
	auto *boardView{new BoardView(this)};

	boardView->setScene(_board);

	_btnRollDice->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	_btnRollDice->setMinimumHeight(100);

	layoutMain->addWidget(boardView);
	layoutMain->addWidget(_btnRollDice);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	setAutoFillBackground(true);
	resize(600, 700);

	connect(_game, &Game::diceRolled, this, &GameWidget::onDiceRolled);
	connect(_game, &Game::bringInChanged, _board, &BoardScene::enableBringIn);
	connect(_game, &Game::possibleMoves, this, &GameWidget::showPossibleMoves);
	connect(_game, &Game::pawnCountChanged, _board, &BoardScene::changePawnCount);
	connect(_game, &Game::nextTurn, this, &GameWidget::onNextTurn);
	connect(_game, &Game::playerWon, this, &GameWidget::onPlayerWon);
	connect(_game, &Game::gameOver, this, &GameWidget::onGameOver);

	connect(_btnRollDice, &QPushButton::clicked, this, &GameWidget::onRollDice);
	connect(boardView, &BoardView::bringPawnIn, _game, &Game::bringPawnIn);
	connect(boardView, &BoardView::movePawn, _game, &Game::movePawn);
}

void GameWidget::onDiceRolled(int score)
{
	_board->setScore(score);
	_board->clearPlayersText();
}

void GameWidget::showPossibleMoves(const QList<int> &moves)
{
	if (_board->canBringIn() || !moves.isEmpty())
		_board->highlightFields(moves);
	else
		_board->setCurrentPlayerText(tr("Can't move."));
}

void GameWidget::onNextTurn(int currentPlayerId)
{
	// m_messageView->clear();
	_btnRollDice->setEnabled(true);
	_board->enableBringIn(false);
	// m_board->setScore(0);
	_board->setCurrentPlayerId(currentPlayerId);
	_board->clearHighlight();
	_board->updateBoard(_game->boardLayout());
}

void GameWidget::onRollDice()
{
	_btnRollDice->setEnabled(false);
	_game->rollDice();
}

void GameWidget::onPlayerWon(int playerId)
{
	// playerWon(playerId);
}

void GameWidget::onGameOver()
{
	// QMessageBox::information(this, "Ludo", "Game over.");
	// _game->reset();
}
