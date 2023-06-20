cmake_minimum_required(VERSION 3.0.0)
project(socket)
# 获取当前目录
link_libraries(task)
aux_source_directory(./ SRC)

# 将源文件添加到库中
add_library(socket ${SRC})
# 任何链接这个库的都可以看到头文件
# target_include_directories(socket PUBLIC ${CMAKE_CURRENT_LIST_DIR})
