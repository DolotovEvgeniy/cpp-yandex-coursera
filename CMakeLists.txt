CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(PROJECT_NAME cpp-yandex-coursera)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/utils")

add_subdirectory(cpp-yandex-03-red)
add_subdirectory(cpp-yandex-04-brown)
