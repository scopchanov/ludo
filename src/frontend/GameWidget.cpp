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
#include "backend/FileManager.h"
#include "backend/engine/Game.h"
#include "frontend/BoardView.h"
#include "frontend/BoardScene.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QBoxLayout>
#include <QPushButton>

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
	connect(_game, &Game::stateChanged, this, &GameWidget::onStateChanged);
	connect(_game, &Game::nextTurn, this, &GameWidget::onNextTurn);
	connect(_game, &Game::playerEscaped, this, &GameWidget::playerWon);
	connect(_game, &Game::gameOver, this, &GameWidget::gameOver);

	connect(_btnRollDice, &QPushButton::clicked, this, &GameWidget::onRollDice);
	connect(boardView, &BoardView::bringPawnIn, _game, &Game::bringPawnIn);
	connect(boardView, &BoardView::movePawn, _game, &Game::movePawn);
}

void GameWidget::startNewGame(const QString &filename)
{
	_filename = filename;
	_game->reset();
	_game->init();
}

void GameWidget::loadGame(const QString &filename)
{
	_filename = filename;
	_game->reset();
	_game->setState(FileManager::openFile(filename));
}

void GameWidget::showActions()
{
	const QList<int> &moves{_game->possibleMoves()};
	bool canBringIn{_game->canBringIn()};

	_board->updateArrows(canBringIn);
    _board->showMoves(moves);

	if (!canBringIn && moves.isEmpty())
		_board->setPlayerText(_game->currentplayer(), tr("Can't move."));
}

void GameWidget::onDiceRolled(int score)
{
	_board->setScore(score);
	_board->clearPlayersText();

	showActions();
}

void GameWidget::onStateChanged()
{
	const QJsonObject &json{_game->state()};

    _board->updateBoard(json.value("board").toObject());
	_board->updateWinners(json.value("winners").toArray());

	FileManager::saveFile(_filename, json);
}

void GameWidget::onNextTurn(int currentplayer)
{
	_btnRollDice->setEnabled(true);
	_board->updateArrows(false);
	_board->highlightPlayer(currentplayer);
	_board->clearHighlight();
}

void GameWidget::onRollDice()
{
	_btnRollDice->setEnabled(false);
	_game->rollDice();
}
