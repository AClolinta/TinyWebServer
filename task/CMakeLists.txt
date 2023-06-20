# 获取当前目录
get_filename_component(CURRENT_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

# 在当前目录中查找源文件
aux_source_directory(${CURRENT_DIR} CURRENT_FILES)

# 将源文件添加到库中
add_library(task ${CURRENT_FILES})
# 任何链接这个库的都可以看到头文件
target_include_directories(task PUBLIC ${CMAKE_CURRENT_LIST_DIR})

#依赖