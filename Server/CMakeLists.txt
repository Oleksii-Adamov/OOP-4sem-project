cmake_minimum_required(VERSION 2.8.4)

project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
                main.cpp

                Database/Database.cpp
                Database/Database.h
                Database/DatabaseLog.cpp
                Database/DatabaseLog.h
                Database/DatabaseService.cpp
                Database/DatabaseService.h

                ../common_src/Entities/Entities.h
                ../common_src/Entities/Entity.cpp
                ../common_src/Entities/Entity.h
                ../common_src/Entities/User.cpp
                ../common_src/Entities/User.h
                ../common_src/Entities/Classroom.cpp
                ../common_src/Entities/Classroom.h
                ../common_src/Entities/StudentClassroom.cpp
                ../common_src/Entities/StudentClassroom.h
                ../common_src/Entities/Authorization.cpp
                ../common_src/Entities/Authorization.h
                ../common_src/Entities/Assignment.cpp
                ../common_src/Entities/Assignment.h
                ../common_src/Entities/AssignmentSession.cpp
                ../common_src/Entities/AssignmentSession.h
                ../common_src/Entities/StudentAssignmentSession.cpp
                ../common_src/Entities/StudentAssignmentSession.h

                Database/Tables/Table.cpp
                Database/Tables/Table.h
                Database/Tables/UserTable.cpp
                Database/Tables/UserTable.h)

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

