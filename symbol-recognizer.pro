QT       += core gui
qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = symbol-recognizer
TEMPLATE = app


SOURCES += \
    main.cpp\
    MainWindow.cpp \
    Perceptron.cpp \
    BitmapForm.cpp \
    ScribbleArea.cpp \
    WeightsModel.cpp

HEADERS  += \
    MainWindow.h \
    Perceptron.h \
    BitmapForm.h \
    ScribbleArea.h \
    Letter.h \
    WeightsModel.h

FORMS    += MainWindow.ui \
    BitmapForm.ui

RESOURCES += \
    res.qrc
