# MIT License

# Copyright (c) 2022-2025 Michael Scopchanov

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

QT += widgets

CONFIG += c++23

SOURCES += \
    backend/FileManager.cpp \
    backend/engine/AbstractGameAction.cpp \
    backend/engine/Base.cpp \
    backend/engine/Board.cpp \
    backend/engine/Dice.cpp \
    backend/engine/Game.cpp \
    backend/engine/MoveAction.cpp \
    backend/engine/Path.cpp \
    backend/engine/Tile.cpp \
    frontend/ArrowItem.cpp \
    frontend/BaseItem.cpp \
    frontend/BoardScene.cpp \
    frontend/BoardView.cpp \
    frontend/DiceItem.cpp \
    frontend/GameMenu.cpp \
    frontend/GameWidget.cpp \
    frontend/HomeItem.cpp \
    frontend/MenuButton.cpp \
    frontend/PlayerItem.cpp \
    frontend/MainWindow.cpp \
    frontend/TileItem.cpp \
    main.cpp

HEADERS += \
    backend/FileManager.h \
    backend/engine/AbstractGameAction.h \
    backend/engine/Base.h \
    backend/engine/Board.h \
    backend/engine/Dice.h \
    backend/engine/Game.h \
    backend/engine/MoveAction.h \
    backend/engine/Path.h \
    backend/engine/Tile.h \
    frontend/ArrowItem.h \
    frontend/BaseItem.h \
    frontend/BoardScene.h \
    frontend/BoardView.h \
    frontend/DiceItem.h \
    frontend/GameMenu.h \
    frontend/GameWidget.h \
    frontend/HomeItem.h \
    frontend/MenuButton.h \
    frontend/PlayerItem.h \
    frontend/TileItem.h \
    frontend/UiGlobals.h \
    frontend/MainWindow.h

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
