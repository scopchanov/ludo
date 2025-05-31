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

#include "MainWindow.h"
#include "GameWidget.h"
#include "GameMenu.h"
#include <QJsonObject>
#include <QStackedLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent),
	_gameMenu{new GameMenu(this)},
	_gameWidget{new GameWidget(this)}
{
	auto *layoutMain{new QStackedLayout(this)};

	layoutMain->addWidget(_gameMenu);
	layoutMain->addWidget(_gameWidget);

	resize(600, 700);

	connect(_gameMenu, &GameMenu::newGame, this, &MainWindow::onNewGame);
	connect(_gameMenu, &GameMenu::loadGame, this, &MainWindow::onLoadGame);
	connect(_gameWidget, &GameWidget::playerWon, this, &MainWindow::onPlayerWon);
	connect(_gameWidget, &GameWidget::gameOver, this, &MainWindow::onGameOver);
}

void MainWindow::onNewGame()
{
	const QString &suggestion{QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm")};
	const QString &filename{QFileDialog::getSaveFileName(this, tr("New game"),
														 "./" + suggestion + ".json",
														 tr("Json-Files (*.json)"))};

	if (filename.isEmpty())
		return;

	_gameWidget->startNewGame(filename);
	stackedLayout()->setCurrentWidget(_gameWidget);
}

void MainWindow::onLoadGame()
{
	const QString &filename{QFileDialog::getOpenFileName(this, tr("Load game"),
														 ".",
														 tr("Json-Files (*.json)"))};

	if (filename.isEmpty())
		return;

	_gameWidget->loadGame(filename);
	stackedLayout()->setCurrentWidget(_gameWidget);
}

void MainWindow::onPlayerWon(int player)
{
	QMessageBox::information(this, "Ludo", tr("Player %1 wins.").arg(player));
}

void MainWindow::onGameOver()
{
	QMessageBox::information(this, "Ludo", tr("Game over!"));
	stackedLayout()->setCurrentWidget(_gameMenu);
}

QStackedLayout *MainWindow::stackedLayout() const
{
	return static_cast<QStackedLayout *>(layout());
}
