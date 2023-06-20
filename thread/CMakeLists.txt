cmake_minimum_required(VERSION 3.0.0)
project(thread)
# 获取当前目录
aux_source_directory(./ SRC)

# 将源文件添加到库中
add_library(thread ${SRC})