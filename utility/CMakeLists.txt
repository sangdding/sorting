
add_library(
        Utility STATIC
        data_generator.cpp
        thread_pool.cpp
        utility.cpp
)

target_include_directories(Utility PUBLIC ${CMAKE_SOURCE_DIR}/includes)