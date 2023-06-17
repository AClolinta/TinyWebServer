cmake_minimum_required(VERSION 3.0.0)
project(TinyWebSever VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()



add_subdirectory(json)
add_subdirectory(log)
add_subdirectory(xml)
add_subdirectory(utility)

add_subdirectory(socket)

add_subdirectory(task)
add_subdirectory(thread)
add_subdirectory(server)

add_subdirectory(engine)
add_subdirectory(plugin)

add_subdirectory(system)

# add_subdirectory(tests)
add_executable(TinyWebSever main.cpp)

##编译依赖
# target_link_libraries(system log utility engine)

##
target_link_libraries(TinyWebSever PUBLIC system log utility server)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# 编译插件 test
set(SRC_PLUGIN_TEST "plugin/TestPlugin.cpp" "json/parser.cpp" "json/json.cpp")
add_library(testplugin SHARED ${SRC_PLUGIN_TEST})

# 编译插件 user
set(SRC_PLUGIN_USER "plugin/UserPlugin.cpp" "json/parser.cpp" "json/json.cpp")
add_library(userplugin SHARED ${SRC_PLUGIN_USER})

# 编译插件 echo
set(SRC_PLUGIN_ECHO "plugin/EchoPlugin.cpp" "log/log.cpp" "system/system.cpp")
add_library(echoplugin SHARED ${SRC_PLUGIN_ECHO})

