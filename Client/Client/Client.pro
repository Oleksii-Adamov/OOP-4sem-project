QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += ../../../boost/boost_1_77_0
INCLUDEPATH += ../../common_src
LIBS += -L../../../boost/boost_1_77_0/stage/lib -llibboost_system-mgw11-mt-x64-1_77
LIBS += -lwsock32
LIBS += -lws2_32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../common_src/assignmentinfo.cpp \
    addeditableheadercommand.cpp \
    addeditabletestanswercommand.cpp \
    addeditabletestassignmentcommand.cpp \
    assignmentcreationwindow.cpp \
    assignmentguibuilder.cpp \
    assignmentguidirector.cpp \
    assignmentslistmodel.cpp \
    authorizationwindow.cpp \
    classroomwindow.cpp \
    classroomwindowstudentstrategy.cpp \
    classroomwindowteacherstrategy.cpp \
    client.cpp \
    command.cpp \
    commandhistory.cpp \
    editablelabel.cpp \
    enterassignmentnamedialog.cpp \
    filepath.cpp \
    font.cpp \
    jsonfile.cpp \
    main.cpp \
    mainwindow.cpp \
    registerwindow.cpp \
    saveeditableassignmentcommand.cpp \
    submitassignment.cpp \
    ../../common_src/testanswer.cpp \
    ../../common_src/testassignment.cpp

HEADERS += \
    ../../common_src/assignmentinfo.h \
    ../../common_src/messagetypes.h \
    addeditableheadercommand.h \
    addeditabletestanswercommand.h \
    addeditabletestassignmentcommand.h \
    assignmentbuilder.h \
    assignmentcreationwindow.h \
    assignmentguibuilder.h \
    assignmentguidirector.h \
    assignmentslistmodel.h \
    authorizationwindow.h \
    classroomwindow.h \
    classroomwindowstrategy.h \
    classroomwindowstudentstrategy.h \
    classroomwindowteacherstrategy.h \
    client.h \
    command.h \
    commandhistory.h \
    editablelabel.h \
    enterassignmentnamedialog.h \
    filepath.h \
    font.h \
    jsonfile.h \
    mainwindow.h \
    registerwindow.h \
    saveeditableassignmentcommand.h \
    submitassignment.h \
    ../../common_src/testanswer.h \
    ../../common_src/testassignment.h
    ../../common_src/net.h

FORMS += \
    assignmentcreationwindow.ui \
    authorizationwindow.ui \
    classroomwindow.ui \
    enterassignmentnamedialog.ui \
    mainwindow.ui \
    registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
