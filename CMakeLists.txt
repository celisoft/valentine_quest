cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 17)
project(valentine_quest)

include(.conan/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB SRC_FILES src/*.cpp)
add_executable(valentine_quest ${SRC_FILES})

file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(valentine_quest ${CONAN_LIBS})