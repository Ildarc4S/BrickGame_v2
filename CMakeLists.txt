cmake_minimum_required(VERSION 3.16)
project(MyQtApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON) 

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -fno-omit-frame-pointer")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
# file(GLOB TETRIS_SOURCES "brick_games/tetris/*.c")
# add_library(s21_tetris STATIC ${TETRIS_SOURCES})
set(TETRIS_LIB_DIR ${CMAKE_SOURCE_DIR}/build/lib)
set(TETRIS_LIB_NAME s21_tetris.a)

find_library(TETRIS_LIB
	NAMES ${TETRIS_LIB_NAME}
	PATHS ${TETRIS_LIB_DIR}
	NO_DEFAULT_PATH
)

if(NOT TETRIS_LIB)
	message(FATAL_ERROR "s21_tetris library not found in ${TETRIS_LIB_DIR}")
endif()

file(GLOB SNAKE_SOURCES "brick_game/snake/*.cpp")
file(GLOB GUI_SOURCES "gui/desktop/*.cpp")
file(GLOB CONTROLLER_SOURCES "common/*.cpp")

add_executable(myapp
    main.cpp
    ${CONTROLLER_SOURCES}
    ${GUI_SOURCES}
    ${SNAKE_SOURCES}
)

add_executable(mytetris
  main.cpp
  ${CONTROLLER_SOURCES}
  ${GUI_SOURCES}
)

target_link_libraries(myapp 
    Qt5::Widgets
)

target_include_directories(mytetris PRIVATE
	${CMAKE_SOURCE_DIR}/brick_games/tetris
)

target_link_libraries(mytetris
	Qt5::Widgets
	${TETRIS_LIB}
)
