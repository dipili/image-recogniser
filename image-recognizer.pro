QT       += core gui
qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image-recognizer
TEMPLATE = app


SOURCES += \
    main.cpp\
    MainWindow.cpp \
    Perceptron.cpp \
    BitmapForm.cpp \
    ScribbleArea.cpp \
    WeightsModel.cpp \
    NeuralNetwork.cpp \
    Utils.cpp \
    DummyNeuralNetworkFactory.cpp

HEADERS  += \
    MainWindow.h \
    Perceptron.h \
    BitmapForm.h \
    ScribbleArea.h \
    Letter.h \
    WeightsModel.h \
    NeuralNetwork.h \
    Utils.h \
    DummyNeuralNetworkFactory.h

FORMS    += \
    MainWindow.ui \
    BitmapForm.ui

RESOURCES += \
    res.qrc
