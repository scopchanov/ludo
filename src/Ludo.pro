QT += widgets

CONFIG += c++17

SOURCES += \
    BoardView.cpp \
    FieldItem.cpp \
    ScoreDisplay.cpp \
    backend/Board.cpp \
    backend/Dice.cpp \
    backend/Field.cpp \
    backend/Game.cpp \
    backend/Pawn.cpp \
    backend/Player.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    BoardView.h \
    FieldItem.h \
    ScoreDisplay.h \
    backend/Board.h \
    backend/Dice.h \
    backend/Field.h \
    backend/Game.h \
    backend/Pawn.h \
    backend/Player.h \
    MainWindow.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
