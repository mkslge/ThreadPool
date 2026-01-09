cmake_minimum_required(VERSION 3.31)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 20)

add_executable(ThreadPool main.cpp
        threadpool.cpp
        threadpool.h
        utility.cpp
        utility.h)
