cmake_minimum_required(VERSION 2.8.4)

project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
                main.cpp

                Database/Database.cpp
                Database/Database.h
                Database/DatabaseLog.cpp
                Database/DatabaseLog.h
                Database/DatabaseTable.cpp
                Database/DatabaseTable.h
                Database/DatabaseService.cpp
                Database/DatabaseService.h

                Database/DatabaseType/DatabaseType.cpp
                Database/DatabaseType/DatabaseType.h
                Database/DatabaseType/DatabaseUserType.cpp
                Database/DatabaseType/DatabaseUserType.h
                Database/DatabaseType/DatabaseClassroomType.cpp
                Database/DatabaseType/DatabaseClassroomType.h
                Database/DatabaseType/DatabaseStudentClassroomType.cpp
                Database/DatabaseType/DatabaseStudentClassroomType.h
                Database/DatabaseType/DatabaseAuthorizationType.cpp
                Database/DatabaseType/DatabaseAuthorizationType.h
                Database/DatabaseType/DatabaseAssignmentType.cpp
                Database/DatabaseType/DatabaseAssignmentType.h
                Database/DatabaseType/DatabaseAssignmentSessionType.cpp
                Database/DatabaseType/DatabaseAssignmentSessionType.h
                Database/DatabaseType/DatabaseStudentAssignmentSessionType.cpp
                Database/DatabaseType/DatabaseStudentAssignmentSessionType.h)

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

