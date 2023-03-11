add_library(json
            json.hpp
            json.cpp
            parser.hpp
            parser.cpp
            )

# 任何链接这个库的都可以看到头文件
target_include_directories(json PUBLIC ${CMAKE_CURRENT_LIST_DIR})