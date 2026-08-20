cmake_minimum_required(VERSION 3.16)
project(whitaker-cpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(whitaker
    src/main.cpp
    src/loaders/dict_loader.cpp
    src/loaders/infl_loader.cpp
    src/loaders/unique_loader.cpp
    src/loaders/addons_loader.cpp
    src/engine.cpp

)

target_include_directories(whitaker PRIVATE include)
