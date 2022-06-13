cmake_minimum_required(VERSION 2.8.4)

project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

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

