cmake_minimum_required(VERSION 3.15)
project(MyProjectTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../)

set(OUT_NAME test_containers.out)
add_compile_definitions(FOR_TEST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -lstdc++ -O0 -Wall -fprofile-arcs -ftest-coverage ")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -fprofile-arcs -ftest-coverage ")

find_package(GTest REQUIRED) # !!!
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(HEADERS
    includes/test_list.h
    ../includes/list.h
)

set(3RD_LIBS gtest pthread)
set(SOURCES
    srcs/test_list.cc
)

add_executable(${OUT_NAME} ${SOURCES} ${HEADERS})

enable_testing()

include_directories(
    ./include
    ../includes
    ${GTEST_INCLUDE_DIRS} # !!!
)

target_include_directories(${OUT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/includes
    ${CMAKE_CURRENT_LIST_DIR}/../
)


target_link_libraries(${OUT_NAME}
    PUBLIC
    ${GTEST_LIBRARIES} # !!!
    Threads::Threads
    ${3RD_LIBS}
)

add_test(NAME ${OUT_NAME} COMMAND ${OUT_NAME})
