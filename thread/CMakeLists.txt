add_library(utility
            iniFile.hpp
            iniFile.cpp
            Singleton.hpp
             
             
            )

# 任何链接这个库的都可以看到头文件
target_include_directories(utility PUBLIC ${CMAKE_CURRENT_LIST_DIR})