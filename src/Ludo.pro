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
    GameMenu.cpp \
    GameWidget.cpp \
    MenuButton.cpp \
    backend/Pathway.cpp \
    backend/Player.cpp \
    frontend/ArrowItem.cpp \
    frontend/BoardScene.cpp \
    frontend/BoardView.cpp \
    frontend/DiceItem.cpp \
    frontend/FieldItem.cpp \
    frontend/HomeItem.cpp \
    frontend/PlayerItem.cpp \
    backend/Board.cpp \
    backend/Dice.cpp \
    backend/Field.cpp \
    backend/Game.cpp \
    backend/Pawn.cpp \
    frontend/SpawnItem.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    GameMenu.h \
    GameWidget.h \
    MenuButton.h \
    backend/Pathway.h \
    backend/Player.h \
    frontend/ArrowItem.h \
    frontend/BoardScene.h \
    frontend/BoardView.h \
    frontend/DiceItem.h \
    frontend/FieldItem.h \
    frontend/HomeItem.h \
    frontend/PlayerItem.h \
    backend/Board.h \
    backend/Dice.h \
    backend/Field.h \
    backend/Game.h \
    backend/Pawn.h \
    MainWindow.h \
    frontend/SpawnItem.h \
    frontend/UiGlobals.h

RESOURCES += \
        resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
