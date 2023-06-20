cmake_minimum_required(VERSION 3.0.0)
project(engine)

link_libraries( xml)

aux_source_directory(./ SRC)

# 将源文件添加到库中
add_library(engine ${SRC})

