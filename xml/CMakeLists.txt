add_library(xml 
            Document.hpp 
            Document.cpp
            Element.hpp
            Element.cpp)

# 任何链接这个库的都可以看到头文件
target_include_directories(xml PUBLIC ${CMAKE_CURRENT_LIST_DIR})