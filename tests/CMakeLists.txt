# include_directories(${CMAKE_SOURCE_DIR}/log)

add_executable(log_test log_test.cpp)
add_executable(json_test json_test.cpp)

target_link_libraries(log_test PUBLIC log)
target_link_libraries(json_test PUBLIC json)

add_test(
    NAME log_test
    COMMAND log_test
)
add_test(
    NAME json_test
    COMMAND json_test
)