QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#DEPENDPATH += . ../Lib
INCLUDEPATH += ../../../boost/boost_1_77_0
INCLUDEPATH += ../../src
LIBS += -L../../../boost/boost_1_77_0/stage/lib -llibboost_system-mgw11-mt-x64-1_77
LIBS += -lwsock32
LIBS += -lws2_32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addeditableheadercommand.cpp \
    addeditabletestanswercommand.cpp \
    addeditabletestassignmentcommand.cpp \
    assignmentcreationwindow.cpp \
    assignmentguibuilder.cpp \
    assignmentguidirector.cpp \
    command.cpp \
    commandhistory.cpp \
    editablelabel.cpp \
    enterassignmentnamedialog.cpp \
    filepath.cpp \
    font.cpp \
    jsonfile.cpp \
    main.cpp \
    mainwindow.cpp \
    saveeditableassignmentcommand.cpp \
    submitassignment.cpp \
    ../../src/testanswer.cpp \
    ../../src/testassignment.cpp

HEADERS += \
    addeditableheadercommand.h \
    addeditabletestanswercommand.h \
    addeditabletestassignmentcommand.h \
    assignmentbuilder.h \
    assignmentcreationwindow.h \
    assignmentguibuilder.h \
    assignmentguidirector.h \
    command.h \
    commandhistory.h \
    editablelabel.h \
    enterassignmentnamedialog.h \
    filepath.h \
    font.h \
    jsonfile.h \
    mainwindow.h \
    saveeditableassignmentcommand.h \
    submitassignment.h \
    ../../src/testanswer.h \
    ../../src/testassignment.h

FORMS += \
    assignmentcreationwindow.ui \
    enterassignmentnamedialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
