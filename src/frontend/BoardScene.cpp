#include "BoardScene.h"
#include "ScoreItem.h"
#include "FieldItem.h"
#include "SpawnItem.h"
#include "ArrowItem.h"
#include "HomeItem.h"
#include "PlayerItem.h"
#include <QJsonObject>
#include <QJsonArray>

BoardScene::BoardScene(QObject *parent) :
    QGraphicsScene{parent},
    m_scoreItem{new ScoreItem()},
    m_currentPlayerId{0},
    m_canBringPawnIn{false}
{
    setSceneRect(-50, -50, 860, 860);

    createPath();
    createIslands();
    createFields();
    createHomes();
    createPlayers();

    m_scoreItem->setPos(380, 380);

    addItem(m_scoreItem);
}

bool BoardScene::canBringIn() const
{
    return m_canBringPawnIn;
}

int BoardScene::currentPlayerId() const
{
    return m_currentPlayerId;
}

void BoardScene::setCurrentPlayerId(int currentPlayerId)
{
    m_currentPlayerId = currentPlayerId;

    m_playerItems.at(m_currentPlayerId)->clear();

    for (auto *player : m_playerItems)
        player->setHighlighted(player->number() == m_currentPlayerId);
}

void BoardScene::setCurrentPlayerText(const QString &str)
{
    m_playerItems.at(m_currentPlayerId)->setText(str);
}

void BoardScene::setScore(int value)
{
    m_scoreItem->setScore(value);
}

void BoardScene::clearHighlight()
{
    for (auto *field : m_fieldItems)
        field->setHighlighted(false);
}

void BoardScene::updateBoard(const QJsonObject &json)
{
    for (auto *field : m_fieldItems)
        field->setPawnColor(QColor());

    const QJsonArray &pathway{json.value("pathway").toArray()};
    const QJsonArray &homes{json.value("homes").toArray()};

    for (const auto &value : pathway) {
        const QJsonObject &field{value.toObject()};
        int n{field.value("number").toInt()};
        int playerId{field.value("player").toInt()};

        m_fieldItems.at(n)->setPawnColor(m_spawnItems.at(playerId)->color());
    }

    for (int n{0}; n < m_homeItems.count(); n++)
        m_homeItems.at(n)->updateItem(homes.at(n).toArray());
}

void BoardScene::enableBringIn(bool canBringIn)
{
    m_canBringPawnIn = canBringIn;

    for (auto *arrow : std::as_const(m_arrowItems))
        arrow->setHighlighted(m_canBringPawnIn
                              && arrow->number() == m_currentPlayerId);
}

void BoardScene::highlightFields(const QList<int> &moves)
{
    for (const auto &move : moves)
        m_fieldItems.at(move)->setHighlighted(true);
}

void BoardScene::changePawnCount(int playerId, int pawnCount)
{
    m_spawnItems.at(playerId)->setPawnCount(pawnCount);
}

void BoardScene::createPath()
{
    addPolygon(QVector<QPointF>{
                   QPoint(310, 730), QPoint(310, 450), QPoint(30, 450),
                   QPoint(30, 310), QPoint(310, 310), QPoint(310, 30),
                   QPoint(450, 30), QPoint(450, 310), QPoint(730, 310),
                   QPoint(730, 450), QPoint(450, 450), QPoint(450, 730)
               }, QPen(QBrush(0x424242), 4));
}

void BoardScene::createIslands()
{
    for (int n{0}; n < 4; n++) {
        auto *island{new SpawnItem(n, playerColor(n))};

        island->setPos(630*(n / 2) + 65, -630*(n / 2 != n % 2) + 695);

        addItem(island);

        m_spawnItems.append(island);

        auto *arrow{new ArrowItem()};

        arrow->setNumber(n);
        arrow->setColor(island->color());
        arrow->setRotation(90*n);

        switch (n) {
        case 0:
            arrow->setPos(205, 730);
            break;
        case 1:
            arrow->setPos(30, 205);
            break;
        case 2:
            arrow->setPos(555, 30);
            break;
        case 3:
            arrow->setPos(730, 555);
            break;
        }

        addItem(arrow);

        m_arrowItems.append(arrow);
    }
}

void BoardScene::createHomes()
{
    for (int n{0}; n < 4; n++) {
        auto *home{new HomeItem(m_spawnItems.at(n)->color())};
        double pi{3.1415};

        home->setPos(175*round(sin((4 - n)*pi/2)) + 380,
                     175*round(cos((4 - n)*pi/2)) + 380);
        home->setRotation(90*n);

        addItem(home);

        m_homeItems.append(home);
    }
}

void BoardScene::createFields()
{
    const QList<int> &directions{2, 3, 2, 1, 2, 1, 0, 1, 0, 3, 0, 3};
    int x{310};
    int y{730};
    int k{-1};

    for (int n{0}; n < 40; n++) {
        auto *field{new FieldItem()};
        int mod10{n % 10};

        field->setNumber(n);
        field->setPos(x, y);

        if (!mod10)
            field->setColor(m_spawnItems.at(n / 10)->color());

        addItem(field);

        m_fieldItems.append(field);

        if (!(mod10 % 4))
            k++;

        int direction{directions.at(k)};

        x = direction == 1 ? x + 70 : direction == 3 ? x - 70 : x;
        y = direction == 0 ? y + 70 : direction == 2 ? y - 70 : y;
    }
}

void BoardScene::createPlayers()
{
    for (int n{0}; n < 4; n++) {
        auto *player{new PlayerItem()};

        player->setNumber(n);
        player->setColor(playerColor(n));

        if (!n)
            player->setHighlighted(true);

        addItem(player);
        m_playerItems.append(player);

        switch (n) {
        case 0:
            player->setPos(190, 570);
            break;
        case 1:
            player->setPos(190, 190);
            break;
        case 2:
            player->setPos(570, 190);
            break;
        case 3:
            player->setPos(570, 570);
            break;
        }
    }
}

int BoardScene::playerColor(int playerId) const
{
    return QList<int>{0x1976D2, 0xFBC02D, 0x388E3C, 0xD32F2F}.at(playerId);
}
