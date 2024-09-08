QT += widgets

CONFIG += c++20

SOURCES += \
    backend/Pathway.cpp \
    backend/Player.cpp \
    frontend/ArrowItem.cpp \
    frontend/BoardScene.cpp \
    frontend/BoardView.cpp \
    frontend/FieldItem.cpp \
    frontend/HomeItem.cpp \
    frontend/PlayerItem.cpp \
    backend/Board.cpp \
    backend/Dice.cpp \
    backend/Field.cpp \
    backend/Game.cpp \
    backend/Pawn.cpp \
    frontend/ScoreItem.cpp \
    frontend/SpawnItem.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    backend/Pathway.h \
    backend/Player.h \
    frontend/ArrowItem.h \
    frontend/BoardScene.h \
    frontend/BoardView.h \
    frontend/FieldItem.h \
    frontend/HomeItem.h \
    frontend/PlayerItem.h \
    backend/Board.h \
    backend/Dice.h \
    backend/Field.h \
    backend/Game.h \
    backend/Pawn.h \
    MainWindow.h \
    frontend/ScoreItem.h \
    frontend/SpawnItem.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
