QT       += core gui
qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = symbol-recognizer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Ciphering/Perceptron.cpp \
    BitmapForm.cpp \
    ScribbleArea.cpp \
    Ciphering/PerceptroNetwork.cpp

HEADERS  += MainWindow.h \
    Ciphering/Perceptron.h \
    BitmapForm.h \
    ScribbleArea.h \
    Ciphering/PerceptroNetwork.h

FORMS    += MainWindow.ui \
    BitmapForm.ui
