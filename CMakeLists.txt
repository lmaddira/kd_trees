cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(kd_trees)

add_executable(kd_trees main.cpp
                        kd_trees.h
                        kd_trees.cpp)

target_include_directories(kd_trees PUBLIC .)