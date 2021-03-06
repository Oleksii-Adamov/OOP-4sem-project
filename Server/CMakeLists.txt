cmake_minimum_required(VERSION 2.8.4)

project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
                main.cpp

                Database/Database.cpp
                Database/Database.h
                Database/DatabaseLog.cpp
                Database/DatabaseLog.h
                Database/DatabaseOperation.h
                Database/DatabaseOperation.cpp

                ../common_src/assignmentinfo.cpp
                ../common_src/assignmentinfo.h
                ../common_src/assignmentsessioninfo.cpp
                ../common_src/assignmentsessioninfo.h
                ../common_src/classroominfo.cpp
                ../common_src/classroominfo.h
                ../common_src/client.h
                ../common_src/common_net.h
                ../common_src/connection.h
                ../common_src/message.h
                ../common_src/messagetypes.h
                ../common_src/net.h
                ../common_src/server.h
                ../common_src/studentassignmentsessioninfo.cpp
                ../common_src/studentassignmentsessioninfo.h
                ../common_src/studentassignmentsessioninfoforteacher.cpp
                ../common_src/studentassignmentsessioninfoforteacher.h
                ../common_src/testanswer.cpp
                ../common_src/testanswer.h
                ../common_src/testassignment.cpp
                ../common_src/testassignment.h
                ../common_src/tsqueue.h

                ../common_src/Entities/Entities.h
                ../common_src/Entities/Entity.h
                ../common_src/Entities/User.h
                ../common_src/Entities/Classroom.h
                ../common_src/Entities/StudentClassroom.h
                ../common_src/Entities/Authorization.h
                ../common_src/Entities/Assignment.h
                ../common_src/Entities/AssignmentSession.h
                ../common_src/Entities/StudentAssignmentSession.h

                Database/SQLite/DatabasePath.h
                Database/SQLite/SQLiteAdapter.cpp
                Database/SQLite/SQLiteAdapter.h
                Database/SQLite/SQLiteService.cpp
                Database/SQLite/SQLiteService.h

                Database/SQLite/sqlite_src/sqlite3.c
                Database/SQLite/sqlite_src/sqlite3.h)

find_package(Boost 1.77.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

if(Boost_FOUND)

    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

endif()

if(MINGW)

    target_link_libraries(${PROJECT_NAME} ws2_32 wsock32)

endif()

