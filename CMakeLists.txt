cmake_minimum_required(VERSION 3.20)
project(Shooter)

set(CMAKE_CXX_STANDARD 17)

set(SHOOTER_SOURCES
    main.cpp
)

add_executable(Shooter ${SHOOTER_SOURCES})