cmake_minimum_required(VERSION 3.0.0)
project(TinyWebSever VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_EXE_LINKER_FLAGS "-lpthread")
# set(CMAKE_CXX_FLAGS "-g -O2 -Wall -Werror -Wno-unused -ldl -fPIC")

##
## 获取当前目录
get_filename_component(CURRENT_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
message(${CURRENT_DIR})

# ## 指定排除的目录
# set(EXCLUDED_DIRECTORIES
#     "${CURRENT_DIR}/build"
#     "${CURRENT_DIR}/plugin"
#     "${CURRENT_DIR}/tests"
# )
# ##获取文件
# file(GLOB_RECURSE SOURCE_FILES
#     "${CURRENT_DIR}/*.cpp"
# )
# ##排除文件
# foreach(EXCLUDED_DIR ${EXCLUDED_DIRECTORIES})
#     file(GLOB_RECURSE EXCLUDED_FILES "${EXCLUDED_DIR}/*")
#     list(REMOVE_ITEM SOURCE_FILES ${EXCLUDED_FILES})
# endforeach()

# foreach(FILE_PATH ${SOURCE_FILES})
#     message("All File : ${FILE_PATH}")
# endforeach()



##设置包含头文件的目录

# 添加所有子目录到包含路径
include_directories(${CURRENT_DIR}/json)
include_directories(${CURRENT_DIR}/logger)
include_directories(${CURRENT_DIR}/xml)
include_directories(${CURRENT_DIR}/utility)
include_directories(${CURRENT_DIR}/socket)
include_directories(${CURRENT_DIR}/task)
include_directories(${CURRENT_DIR}/thread)
include_directories(${CURRENT_DIR}/server)
include_directories(${CURRENT_DIR}/engine)
include_directories(${CURRENT_DIR}/plugin)
include_directories(${CURRENT_DIR}/system)

# 获取所有的包含路径
get_property(include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)

# 打印包含路径
foreach(dir ${include_dirs})
    message("Include Directory: ${dir}")
endforeach()

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
# add_subdirectory(plugin)
add_subdirectory(system)

##链接
link_libraries(xml logger utility json server task thread socket engine sys)

##可执行文件
add_executable(TinyWebSever main.cpp)
# add_executable(TinyWebSever ${SOURCE_FILES})

##

# target_link_libraries(TinyWebSever utility)
# target_link_libraries(TinyWebSever xml)
# target_link_libraries(TinyWebSever json)
# target_link_libraries(TinyWebSever server)
# target_link_libraries(TinyWebSever task)
# target_link_libraries(TinyWebSever thread)
# target_link_libraries(TinyWebSever socket)
# target_link_libraries(TinyWebSever engine)
# target_link_libraries(TinyWebSever system)

# target_link_libraries(TinyWebSever plugin)

## 插件编译
#编译插件 test
# set(SRC_PLUGIN_TEST "plugin/TestPlugin.cpp" "json/parser.cpp" "json/json.cpp")
# add_library(testplugin SHARED ${SRC_PLUGIN_TEST})

# # 编译插件 user
# set(SRC_PLUGIN_USER "plugin/UserPlugin.cpp" "json/parser.cpp" "json/json.cpp")
# add_library(userplugin SHARED ${SRC_PLUGIN_USER})

# # 编译插件 echo
# set(SRC_PLUGIN_ECHO "plugin/EchoPlugin.cpp" "logger/log.cpp" "system/system.cpp")
# add_library(echoplugin SHARED ${SRC_PLUGIN_ECHO})

