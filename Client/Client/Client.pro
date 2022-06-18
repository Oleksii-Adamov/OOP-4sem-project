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
    ../../common_src/classroominfo.cpp \
    ../../common_src/studentassignmentsessioninfo.cpp \
    addeditableheadercommand.cpp \
    addeditabletestanswercommand.cpp \
    addeditabletestassignmentcommand.cpp \
    assignmentcreationwindow.cpp \
    assignmentguibuilder.cpp \
    assignmentguidirector.cpp \
    assignmentslistmodel.cpp \
    assignmentsnamelistmodel.cpp \
    authorizationwindow.cpp \
    classroomslistmodel.cpp \
    classroomslistwindow.cpp \
    classroomsnamelistmodel.cpp \
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
    mainmenuwindow.cpp \
    mainwindow.cpp \
    registerwindow.cpp \
    saveeditableassignmentcommand.cpp \
    sendassignmentwindow.cpp \
    studentassignmentsessionslistmodel.cpp \
    studentassignmentsessionswindow.cpp \
    submitassignment.cpp \
    ../../common_src/testanswer.cpp \
    ../../common_src/testassignment.cpp \
    teacherassignmentcheckingwindow.cpp

HEADERS += \
    ../../common_src/assignmentinfo.h \
    ../../common_src/classroominfo.h \
    ../../common_src/messagetypes.h \
    ../../common_src/studentassignmentsessioninfo.h \
    addeditableheadercommand.h \
    addeditabletestanswercommand.h \
    addeditabletestassignmentcommand.h \
    assignmentbuilder.h \
    assignmentcreationwindow.h \
    assignmentguibuilder.h \
    assignmentguidirector.h \
    assignmentslistmodel.h \
    assignmentsnamelistmodel.h \
    authorizationwindow.h \
    classroomslistmodel.h \
    classroomslistwindow.h \
    classroomsnamelistmodel.h \
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
    mainmenuwindow.h \
    mainwindow.h \
    registerwindow.h \
    saveeditableassignmentcommand.h \
    sendassignmentwindow.h \
    studentassignmentsessionslistmodel.h \
    studentassignmentsessionswindow.h \
    submitassignment.h \
    ../../common_src/testanswer.h \
    ../../common_src/testassignment.h \
    teacherassignmentcheckingwindow.h
    ../../common_src/net.h

FORMS += \
    assignmentcreationwindow.ui \
    authorizationwindow.ui \
    classroomslistwindow.ui \
    classroomwindow.ui \
    enterassignmentnamedialog.ui \
    mainmenuwindow.ui \
    mainwindow.ui \
    registerwindow.ui \
    sendassignmentwindow.ui \
    studentassignmentsessionswindow.ui \
    teacherassignmentcheckingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
