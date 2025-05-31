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

#include "Game.h"
#include "Dice.h"
#include "Board.h"
#include <QJsonObject>
#include <QJsonArray>

Game::Game(QObject *parent) :
    QObject{parent},
    _dice{new Dice(this)},
    _board{new Board(this)},
    _playerCount{4},
    _currentPlayerId{0}
{
    connect(_board, &Board::playerEscaped, this, &Game::onPlayerEscaped);
}

QJsonObject Game::state() const
{
    return QJsonObject{{"currentPlayer", _currentPlayerId},
                       {"score", _dice->score()},
                       {"board", _board->state()}};
}

void Game::setState(const QJsonObject &json)
{
    _currentPlayerId = json.value("currentPlayer").toInt();
    _dice->setScore(json.value("score").toInt());
    _board->setState(json.value("board").toObject());

    emit stateChanged();
    advance();
}

int Game::currentPlayerId() const
{
    return _currentPlayerId;
}

bool Game::canBringIn() const
{
    return _dice->score() == 6 && _board->canBringIn(_currentPlayerId);
}

QList<int> Game::possibleMoves() const
{
    return _board->findPossibleMoves(_currentPlayerId, _dice->score());
}

void Game::rollDice()
{
    _dice->roll();

    QList<int> moves{_board->findPossibleMoves(_currentPlayerId, _dice->score())};
    bool canBringPawnIn{canBringIn()};

    emit diceRolled(_dice->score());

    if (!canBringPawnIn && moves.isEmpty())
        advance();
}

void Game::bringPawnIn()
{
    if (!_board->bringPawnIn(_currentPlayerId))
        return;

    emit stateChanged();
    advance();
}

void Game::movePawn(int srcTileIndex)
{
    if (!_board->movePawn(_currentPlayerId, srcTileIndex, _dice->score()))
        return;

    emit stateChanged();
    advance();
}

void Game::init()
{
    _board->init();
    emit stateChanged();
}

void Game::reset()
{
    _winners.clear();
    _board->reset();
    _currentPlayerId = 0;

    emit nextTurn(_currentPlayerId);
}

void Game::advance()
{
    if (_dice->score() != 6)
        switchToNextPlayer();

    emit nextTurn(_currentPlayerId);
}

void Game::switchToNextPlayer()
{
    _currentPlayerId++;
    _currentPlayerId %= _playerCount;

    if (_winners.contains(_currentPlayerId))
        switchToNextPlayer();
}

void Game::onPlayerEscaped(int playerId)
{
    _winners.append(playerId);
    emit playerEscaped(playerId);

    if (_winners.count() == _playerCount - 1)
        emit gameOver();
}
