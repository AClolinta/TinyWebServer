cmake_minimum_required(VERSION 3.0.0)
project(TinyWebSever VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_executable(TinyWebSever main.cpp)

add_subdirectory(log)
add_subdirectory(tests)
add_subdirectory(json)
add_subdirectory(utility)
add_subdirectory(xml)
add_subdirectory(thread)
# add_subdirectory(engine)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
