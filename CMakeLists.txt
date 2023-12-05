cmake_minimum_required(VERSION 3.15)

project(Containers_stl LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(OUT_NAME containers_stl)

# set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(HEADERS
    s21_array.h
    s21_containers.h
    s21_containersplus.h
    s21_list.h
    s21_map.h
    s21_multiset.h
    s21_queue.h
    s21_set.h
    s21_stack.h
    s21_vector.h
    general_btee.h
)

set(SOURCES
    ./test/containers_test.cc
)

add_executable(${OUT_NAME} ${SOURCES} ${HEADERS})

enable_testing()

include_directories(
    ./test/
    ${GTEST_INCLUDE_DIRS}
)

target_include_directories(${OUT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)


target_link_libraries(${OUT_NAME}
    PUBLIC
    ${GTEST_LIBRARIES}
    Threads::Threads)

add_test(NAME ${OUT_NAME} COMMAND ${OUT_NAME})

