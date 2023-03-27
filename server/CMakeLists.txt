add_library(server system.hpp system.cpp)

# 任何链接这个库的都可以看到头文件
target_include_directories(system PUBLIC ${CMAKE_CURRENT_LIST_DIR})