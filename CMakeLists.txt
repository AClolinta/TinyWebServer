cmake_minimum_required(VERSION 3.0.0)
project(TinyWebSever VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS "-g -O2 -Wall -Werror -Wno-unused -ldl -fPIC")

include(CTest)
include(CPack)
enable_testing()

##
add_subdirectory(json)
add_subdirectory(logger)
add_subdirectory(xml)
add_subdirectory(utility)
add_subdirectory(socket)
add_subdirectory(task)
add_subdirectory(thread)
add_subdirectory(server)
add_subdirectory(engine)
add_subdirectory(plugin)
add_subdirectory(system)
add_subdirectory(tests)

##可执行文件
add_executable(TinyWebSever main.cpp)

##编译依赖

# target_link_libraries(TinyWebSever json)
# target_link_libraries(TinyWebSever xml)
# target_link_libraries(TinyWebSever logger)
# target_link_libraries(TinyWebSever utility)

target_link_libraries(TinyWebSever server)
target_link_libraries(TinyWebSever socket)
target_link_libraries(TinyWebSever thread)
target_link_libraries(TinyWebSever system)
target_link_libraries(TinyWebSever task)

target_link_libraries(TinyWebSever engine)
target_link_libraries(TinyWebSever plugin)
##
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

## 插件编译
#编译插件 test
set(SRC_PLUGIN_TEST "plugin/TestPlugin.cpp" "json/parser.cpp" "json/json.cpp")
add_library(testplugin SHARED ${SRC_PLUGIN_TEST})

# 编译插件 user
set(SRC_PLUGIN_USER "plugin/UserPlugin.cpp" "json/parser.cpp" "json/json.cpp")
add_library(userplugin SHARED ${SRC_PLUGIN_USER})

# 编译插件 echo
set(SRC_PLUGIN_ECHO "plugin/EchoPlugin.cpp" "logger/log.cpp" "system/system.cpp")
add_library(echoplugin SHARED ${SRC_PLUGIN_ECHO})

