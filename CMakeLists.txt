cmake_minimum_required(VERSION 3.16)
project(MyQtApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON) 

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB SNAKE_SOURCES "brick_game/snake/*.cpp")
file(GLOB GUI_SOURCES "gui/desktop/*.cpp")
file(GLOB CONTROLLER_SOURCES "common/*.cpp")

add_executable(myapp
    main.cpp
    ${CONTROLLER_SOURCES}
    ${GUI_SOURCES}
    ${SNAKE_SOURCES}
)

target_link_libraries(myapp 
    Qt5::Widgets
)
