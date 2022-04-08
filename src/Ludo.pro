QT += widgets

CONFIG += c++17

SOURCES += \
    frontend/ArrowItem.cpp \
    frontend/BoardScene.cpp \
    frontend/BoardView.cpp \
    frontend/FieldItem.cpp \
    frontend/PlayerItem.cpp \
    frontend/ScoreDisplay.cpp \
    backend/Board.cpp \
    backend/Dice.cpp \
    backend/Field.cpp \
    backend/Game.cpp \
    backend/Pawn.cpp \
    backend/Player.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    frontend/ArrowItem.h \
    frontend/BoardScene.h \
    frontend/BoardView.h \
    frontend/FieldItem.h \
    frontend/PlayerItem.h \
    frontend/ScoreDisplay.h \
    backend/Board.h \
    backend/Dice.h \
    backend/Field.h \
    backend/Game.h \
    backend/Pawn.h \
    backend/Player.h \
    MainWindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
