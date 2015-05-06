#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T16:41:55
#
#-------------------------------------------------
cache()  # apparently speeds up qmake, as suggested by warning

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Imago
TEMPLATE = app

# Modify to reflect your installation path
INCLUDEPATH += "/usr/local/include"
INCLUDEPATH += "/usr/local/include/opencv"
INCLUDEPATH += "/usr/local/include/opencv2"

# Modify to reflect your isntallation path
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree
LIBS += -lopencv_stitching


SOURCES += main.cpp\
        imago.cpp \
    iprocesstechnique.cpp \
    flipimage.cpp \
    processmanager.cpp \
    saltandpepper.cpp \
    histogramequalize.cpp \
    morphologyoperation.cpp \
    lowpassfilter.cpp \
    cannyedgedetector.cpp \
    stringsglobals.cpp

HEADERS  += imago.h \
    iprocesstechnique.h \
    flipimage.h \
    processmanager.h \
    allalgorithms.h \
    saltandpepper.h \
    histogramequalize.h \
    stringsglobals.h \
    morphologyoperation.h \
    lowpassfilter.h \
    cannyedgedetector.h

FORMS    += imago.ui


# references used for this project (cited next to corresponding code)
OTHER_FILES += \
    References.txt

# resource file to contain default image, icon images ...
RESOURCES += \
    resource.qrc
