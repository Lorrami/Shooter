cmake_minimum_required(VERSION 3.20)
project(Shooter)

set(CMAKE_CXX_STANDARD 17)

set(SHOOTER_SOURCES
 "main.cpp"
 "Application.cpp" 
 "Level.cpp" "GameObject.cpp" "Player.cpp")

add_subdirectory(thirdparty/SFML)

add_executable(Shooter ${SHOOTER_SOURCES})
target_link_libraries(Shooter sfml-graphics sfml-system sfml-window)