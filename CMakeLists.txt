cmake_minimum_required(VERSION 3.16)
project(MyQtApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON) 

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(myapp
    main.cpp
)

target_link_libraries(myapp 
    Qt5::Widgets
)
