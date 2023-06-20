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
## 获取当前目录
get_filename_component(CURRENT_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
message(${CURRENT_DIR})

# 指定排除的目录
set(EXCLUDED_DIRECTORIES
    "${CURRENT_DIR}/build"
    "${CURRENT_DIR}/plugin"
)
##获取文件
file(GLOB_RECURSE SOURCE_FILES
    "${CURRENT_DIR}/*.cpp"
)
##排除文件
foreach(EXCLUDED_DIR ${EXCLUDED_DIRECTORIES})
    file(GLOB_RECURSE EXCLUDED_FILES "${EXCLUDED_DIR}/*")
    list(REMOVE_ITEM SOURCE_FILES ${EXCLUDED_FILES})
endforeach()

foreach(FILE_PATH ${SOURCE_FILES})
    message("${FILE_PATH}\n")
endforeach()

##可执行文件
add_executable(TinyWebSever ${SOURCE_FILES})

##链接依赖的库

##头文件
# target_include_directories(TinyWebSever PUBLIC ${CURRENT_DIR})

##
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

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

