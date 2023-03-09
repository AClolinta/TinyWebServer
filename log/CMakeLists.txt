add_library(log log.hpp log.cpp)

# 任何链接这个库的都可以看到头文件
target_include_directories(log PUBLIC ${CMAKE_CURRENT_LIST_DIR})