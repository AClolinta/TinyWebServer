cmake_minimum_required(VERSION 3.0.0)
project(TinyWebSever VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_executable(TinyWebSever main.cpp)

add_subdirectory(engine)
add_subdirectory(json)
add_subdirectory(log)
add_subdirectory(plugin)
add_subdirectory(server)
add_subdirectory(socket)
add_subdirectory(system)
add_subdirectory(task)
add_subdirectory(thread)
add_subdirectory(utility)
add_subdirectory(xml)

add_subdirectory(tests)

target_link_libraries(TinyWebSever engine)
target_link_libraries(TinyWebSever json)
target_link_libraries(TinyWebSever log)
target_link_libraries(TinyWebSever plugin)
target_link_libraries(TinyWebSever server)
target_link_libraries(TinyWebSever socket)
target_link_libraries(TinyWebSever system)
target_link_libraries(TinyWebSever task)
target_link_libraries(TinyWebSever thread)
target_link_libraries(TinyWebSever utility)
target_link_libraries(TinyWebSever xml)


# # 找出当前目录下所有的源文件（以.cpp结尾）
# file(GLOB_RECURSE SRCS "*.cpp")

# # 编译主程序
# set(SRC_MAIN "main.cpp")
# add_executable(main ${SRC_MAIN} ${SRCS})

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
