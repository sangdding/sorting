cmake_minimum_required(VERSION 3.22)

project(Main)
set(CMAKE_CXX_STANDARD 20)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(TBB REQUIRED)
find_package(OpenMP)

if(OpenMP_CXX_FOUND)
    add_compile_options(${OpenMP_CXX_FLAGS})
    link_libraries(OpenMP::OpenMP_CXX)
endif()


set(CMAKE_THREAD_LIBS_INIT "-lpthread")

add_subdirectory(./utility)
add_executable(Main main.cpp)
add_executable(Learn learn.cpp)
add_executable(Test test.cpp)
add_executable(DataSize dataSize.cpp)
add_executable(Parallel parallel.cpp)
add_compile_options(-march=native -mcx16)

target_link_libraries(Main PUBLIC Threads::Threads)
target_link_libraries(Main PRIVATE TBB::tbb)
target_link_libraries(Main PUBLIC Utility)
target_link_libraries(Main PUBLIC -latomic)

target_link_libraries(Learn PUBLIC Threads::Threads)
target_link_libraries(Learn PRIVATE TBB::tbb)
target_link_libraries(Learn PUBLIC Utility)
target_link_libraries(Learn PUBLIC -latomic)

target_link_libraries(Test PUBLIC Threads::Threads)
target_link_libraries(Test PRIVATE TBB::tbb)
target_link_libraries(Test PUBLIC Utility)
target_link_libraries(Test PUBLIC -latomic)

target_link_libraries(DataSize PUBLIC Threads::Threads)
target_link_libraries(DataSize PRIVATE TBB::tbb)
target_link_libraries(DataSize PUBLIC Utility)
target_link_libraries(DataSize PUBLIC -latomic)

target_link_libraries(Parallel PUBLIC Threads::Threads)
target_link_libraries(Parallel PRIVATE TBB::tbb)
target_link_libraries(Parallel PUBLIC Utility)
target_link_libraries(Parallel PUBLIC -latomic)