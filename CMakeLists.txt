cmake_minimum_required(VERSION 3.26)
project(scroll-shooter)

set(CMAKE_CXX_STANDARD 23)

add_executable(scroll-shooter scroll-shooter/main.cpp
        scroll-shooter/AllyShip.cpp
        scroll-shooter/Asteroid.cpp
        scroll-shooter/Bullet.cpp
        scroll-shooter/EnemyShip.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS graphics window network audio REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(scroll-shooter
        sfml-graphics
        sfml-window
        sfml-network
        sfml-audio)
