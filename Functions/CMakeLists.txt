cmake_minimum_required(VERSION 3.10)
project(Tree
        VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main src/main.cpp)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(Tree src/Tree.cpp)
target_include_directories(Tree PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(Node src/Node.cpp)
target_include_directories(Node PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(main Tree)
target_link_libraries(main Node)



