QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += ../../../boost/boost_1_77_0
INCLUDEPATH += ../../common_src
INCLUDEPATH += ../../common_src/Entities
LIBS += -L../../../boost/boost_1_77_0/stage/lib -llibboost_system-mgw11-mt-x64-1_77
LIBS += -lwsock32
LIBS += -lws2_32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../common_src/assignmentinfo.cpp \
    ../../common_src/assignmentsessioninfo.cpp \
    ../../common_src/classroominfo.cpp \
    ../../common_src/studentassignmentsessioninfo.cpp \
    ../../common_src/studentassignmentsessioninfoforteacher.cpp \
    addeditableheadercommand.cpp \
    addeditabletestanswercommand.cpp \
    addeditabletestassignmentcommand.cpp \
    assignmentcreationwindow.cpp \
    assignmentguibuilder.cpp \
    assignmentguidirector.cpp \
    assignmentsessionslistmodel.cpp \
    assignmentslistmodel.cpp \
    authorizationwindow.cpp \
    checkassignment.cpp \
    checkclientthread.cpp \
    classroomslistmodel.cpp \
    classroomslistwindow.cpp \
    classroomsnamelistmodel.cpp \
    classroomwindow.cpp \
    classroomwindowstudentstrategy.cpp \
    classroomwindowteacherstrategy.cpp \
    client.cpp \
    clientsubscriber.cpp \
    clientsubscribergui.cpp \
    command.cpp \
    commandhistory.cpp \
    createclassroomdialog.cpp \
    createdassignmentswindow.cpp \
    editablelabel.cpp \
    enterassignmentnamedialog.cpp \
    filepath.cpp \
    font.cpp \
    joinclassroomdialog.cpp \
    jsonfile.cpp \
    main.cpp \
    mainmenuwindow.cpp \
    mainwindow.cpp \
    registerwindow.cpp \
    saveeditableassignmentcommand.cpp \
    sendassignmentwindow.cpp \
    serverdowndialog.cpp \
    studentassignmentsessionsforteacherlistmodel.cpp \
    studentassignmentsessionslistmodel.cpp \
    studentassignmentsessionswindow.cpp \
    studentassignmentwindow.cpp \
    submitassignment.cpp \
    ../../common_src/testanswer.cpp \
    ../../common_src/testassignment.cpp \
    teacherassignmentcheckingwindow.cpp \
#    ../../common_src/Entities/Assignment.cpp \
#    ../../common_src/Entities/AssignmentSession.cpp \
#    ../../common_src/Entities/AssignmentSession.cpp \
#    ../../common_src/Entities/Authorization.cpp \
#    ../../common_src/Entities/Classroom.cpp \
#    ../../common_src/Entities/StudentAssignmentSession.cpp \
#    ../../common_src/Entities/StudentClassroom.cpp \
#    ../../common_src/Entities/User.cpp \
#    ../../common_src/Entities/Entity.cpp \

HEADERS += \
    ../../common_src/assignmentinfo.h \
    ../../common_src/assignmentsessioninfo.h \
    ../../common_src/classroominfo.h \
    ../../common_src/messagetypes.h \
    ../../common_src/studentassignmentsessioninfo.h \
    ../../common_src/studentassignmentsessioninfoforteacher.h \
    addeditableheadercommand.h \
    addeditabletestanswercommand.h \
    addeditabletestassignmentcommand.h \
    assignmentbuilder.h \
    assignmentcreationwindow.h \
    assignmentguibuilder.h \
    assignmentguidirector.h \
    assignmentsessionslistmodel.h \
    assignmentslistmodel.h \
    authorizationwindow.h \
    checkassignment.h \
    checkclientthread.h \
    classroomslistmodel.h \
    classroomslistwindow.h \
    classroomsnamelistmodel.h \
    classroomwindow.h \
    classroomwindowstrategy.h \
    classroomwindowstudentstrategy.h \
    classroomwindowteacherstrategy.h \
    client.h \
    clientsubscriber.h \
    clientsubscribergui.h \
    command.h \
    commandhistory.h \
    createclassroomdialog.h \
    createdassignmentswindow.h \
    editablelabel.h \
    enterassignmentnamedialog.h \
    filepath.h \
    font.h \
    joinclassroomdialog.h \
    jsonfile.h \
    mainmenuwindow.h \
    mainwindow.h \
    registerwindow.h \
    saveeditableassignmentcommand.h \
    sendassignmentwindow.h \
    serverdowndialog.h \
    studentassignmentsessionsforteacherlistmodel.h \
    studentassignmentsessionslistmodel.h \
    studentassignmentsessionswindow.h \
    studentassignmentwindow.h \
    submitassignment.h \
    ../../common_src/testanswer.h \
    ../../common_src/testassignment.h \
    teacherassignmentcheckingwindow.h \
    ../../common_src/net.h \
    ../../common_src/Entities/Assignment.h \
    ../../common_src/Entities/AssignmentSession.h \
    ../../common_src/Entities/AssignmentSession.h \
    ../../common_src/Entities/Authorization.h \
    ../../common_src/Entities/Classroom.h \
    ../../common_src/Entities/StudentAssignmentSession.h \
    ../../common_src/Entities/StudentClassroom.h \
    ../../common_src/Entities/User.h
    ../../common_src/Entities/Entity.h

FORMS += \
    assignmentcreationwindow.ui \
    authorizationwindow.ui \
    classroomslistwindow.ui \
    classroomwindow.ui \
    createclassroomdialog.ui \
    createdassignmentswindow.ui \
    enterassignmentnamedialog.ui \
    joinclassroomdialog.ui \
    mainmenuwindow.ui \
    mainwindow.ui \
    registerwindow.ui \
    sendassignmentwindow.ui \
    serverdowndialog.ui \
    studentassignmentsessionswindow.ui \
    studentassignmentwindow.ui \
    teacherassignmentcheckingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
