cmake_minimum_required(VERSION 3.0.0)
project(plugin)
# 获取当前目录
aux_source_directory(./ SRC)

# 将源文件添加到库中
add_library(plugin SHARED ${SRC})
# 任何链接这个库的都可以看到头文件
# target_include_directories(plugin PUBLIC ${CMAKE_CURRENT_LIST_DIR})