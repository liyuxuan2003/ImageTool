#-------------------------------------------------
#
# Project created by QtCreator 2019-06-21T13:52:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    LiLibrary/LiEasyLayout.cpp \
    LiLibrary/LiFileName.cpp \
    Menu.cpp \
    FormatMenu.cpp \
    LiLibrary/LiFixedToLayout.cpp \
    FormatProcess.cpp \
    ProcessThread.cpp \
    CropMenu.cpp \
    CropProcess.cpp \
    CompressMenu.cpp \
    LiLibrary/LiReadImageInfo.cpp \
    CompressProcess.cpp \
    ConnectMenu.cpp \
    ConnectProcess.cpp \
    ExampleProcess.cpp \
    ConnectThread.cpp

HEADERS += \
        MainWindow.h \
    LiLibrary/LiEasyLayout.h \
    LiLibrary/LiFileName.h \
    Menu.h \
    FormatMenu.h \
    LiLibrary/LiFixedToLayout.h \
    FormatProcess.h \
    ProcessThread.h \
    CropMenu.h \
    CropProcess.h \
    CompressMenu.h \
    LiLibrary/LiReadImageInfo.h \
    CompressProcess.h \
    ConnectMenu.h \
    ConnectProcess.h \
    ExampleProcess.h \
    ConnectThread.h

FORMS += \
        MainWindow.ui \
    Menu.ui \
    FormatMenu.ui \
    FormatProcess.ui \
    CropMenu.ui \
    CropProcess.ui \
    CompressMenu.ui \
    CompressProcess.ui \
    ConnectMenu.ui \
    ConnectProcess.ui \
    ExampleProcess.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Icon/Exit-3780.PNG \
    Icon/Format-3780.PNG \
    Icon/Frame-3780.PNG \
    Icon/Help-3780.PNG \
    Icon/MakeGif-3780.PNG \
    Icon/ProjectIcon-3780.PNG \
    Icon/UnderDevelop-3780.PNG \
    Icon/WaterMark-3780.PNG \
    Icon/MakeIcon-3780.PNG \
    Icon/Start-3780.PNG \
    Icon/CropPercent-3780.PNG \
    Icon/CropPixel-3780.PNG \
    Icon/CropPercentHeight-3780.PNG \
    Icon/CropPercentWidth-3780.PNG \
    Icon/Compress-3780.PNG \
    Icon/CompressPercent-3780.PNG \
    Icon/CompressPixel-3780.PNG \
    Icon/Connect-3780.PNG \
    Icon/Crop-3780.PNG \
    Icon/CropPercent-3780.PNG \
    Icon/CropPercentHeight-3780.PNG \
    Icon/CropPercentWidth-3780.PNG \
    Icon/CropPixel-3780.PNG \
    Icon/Exit-3780.PNG \
    Icon/Format-3780.PNG \
    Icon/Frame-3780.PNG \
    Icon/Help-3780.PNG \
    Icon/MakeGif-3780.PNG \
    Icon/MakeIcon-3780.PNG \
    Icon/ProjectIcon-3780.PNG \
    Icon/Start-3780.PNG \
    Icon/UnderDevelop-3780.PNG \
    Icon/WaterMark-3780.PNG \
    Icon/Compress-3780.PNG \
    Icon/CompressPercent-3780.PNG \
    Icon/CompressPixel-3780.PNG \
    Icon/Connect-3780.PNG \
    Icon/Crop-3780.PNG \
    Icon/CropPercent-3780.PNG \
    Icon/CropPercentHeight-3780.PNG \
    Icon/CropPercentWidth-3780.PNG \
    Icon/CropPixel-3780.PNG \
    Icon/Exit-3780.PNG \
    Icon/Format-3780.PNG \
    Icon/Frame-3780.PNG \
    Icon/Help-3780.PNG \
    Icon/MakeGif-3780.PNG \
    Icon/MakeIcon-3780.PNG \
    Icon/ProjectIcon-3780.PNG \
    Icon/Start-3780.PNG \
    Icon/UnderDevelop-3780.PNG \
    Icon/WaterMark-3780.PNG \
    Icon/ConnectHorizontal-3780.PNG \
    Icon/ConnectMatrix-3780.PNG \
    Icon/ConnectVertical-3780.PNG

RESOURCES += \
    Icon.qrc
