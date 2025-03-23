cmake_minimum_required(VERSION 3.16)
project(BrickGame LANGUAGES CXX C)

# Настройки стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройки стандарта C (для ncurses)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Включение автоматической генерации MOC, RCC и UIC для Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Флаги компиляции
add_compile_options(-Wall -Wextra -Werror)

# Поиск Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Пути к исходным файлам и директориям
set(SNAKE_SRC_DIR ${CMAKE_SOURCE_DIR}/brick_game/snake)
set(TETRIS_SRC_DIR ${CMAKE_SOURCE_DIR}/brick_game/tetris)
set(GUI_CLI_DIR ${CMAKE_SOURCE_DIR}/gui/cli)
set(GUI_DESKTOP_DIR ${CMAKE_SOURCE_DIR}/gui/desktop)
set(GUI_COMMON_DIR ${CMAKE_SOURCE_DIR}/gui/common)
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(OBJ_SNAKE_DIR ${BUILD_DIR}/obj/snake)
set(OBJ_TETRIS_DIR ${BUILD_DIR}/obj/tetris)
set(OBJ_CLI_DIR ${BUILD_DIR}/obj/cli)
set(SNAKE_BIN_DIR ${CMAKE_SOURCE_DIR}/bin/snake)  # Для Snake
set(TETRIS_BIN_DIR ${CMAKE_SOURCE_DIR}/bin/tetris)  # Для Tetris
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

# Имена файлов
set(SNAKE_LIB_NAME s21_snake)
set(TETRIS_LIB_NAME s21_tetris)
set(SNAKE_DESKTOP_EXEC s21_snake_desktop)
set(SNAKE_CLI_EXEC s21_snake_cli)
set(TETRIS_DESKTOP_EXEC s21_tetris_desktop)
set(TETRIS_CLI_EXEC s21_tetris_cli)

# Создание директорий
file(MAKE_DIRECTORY ${LIB_DIR})
file(MAKE_DIRECTORY ${SNAKE_BIN_DIR})
file(MAKE_DIRECTORY ${TETRIS_BIN_DIR})
file(MAKE_DIRECTORY ${OBJ_SNAKE_DIR})
file(MAKE_DIRECTORY ${OBJ_TETRIS_DIR})
file(MAKE_DIRECTORY ${OBJ_CLI_DIR})

# Поиск исходных файлов
file(GLOB SNAKE_SOURCES "${SNAKE_SRC_DIR}/*.cpp")
file(GLOB TETRIS_SOURCES "${TETRIS_SRC_DIR}/*.cpp")
file(GLOB GUI_CLI_SOURCES "${GUI_CLI_DIR}/*.c")
file(GLOB GUI_DESKTOP_SOURCES "${GUI_DESKTOP_DIR}/*.cpp")
file(GLOB GUI_COMMON_SOURCES "${GUI_COMMON_DIR}/*.cpp")

# Создание библиотеки s21_snake.a из brick_game/snake
add_library(snake_lib STATIC ${SNAKE_SOURCES})
set_target_properties(snake_lib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}
    OUTPUT_NAME ${SNAKE_LIB_NAME}
    PREFIX ""
    OBJECT_OUTPUT_DIRECTORY ${OBJ_SNAKE_DIR}
)
target_include_directories(snake_lib PUBLIC ${SNAKE_SRC_DIR})

# Проверка наличия s21_tetris.a и вызов Makefile, если его нет
if(NOT EXISTS "${LIB_DIR}/${TETRIS_LIB_NAME}.a")
    message(STATUS "s21_tetris.a not found in ${LIB_DIR}, building it with Makefile")
    execute_process(
        COMMAND make s21_tetris.a
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE MAKE_RESULT
    )
    if(NOT MAKE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to build s21_tetris.a with Makefile")
    endif()
endif()

# Создание библиотеки s21_tetris.a как внешней (уже собранной)
add_library(tetris_lib STATIC IMPORTED)
set_target_properties(tetris_lib PROPERTIES
    IMPORTED_LOCATION ${LIB_DIR}/${TETRIS_LIB_NAME}.a
    INTERFACE_INCLUDE_DIRECTORIES ${TETRIS_SRC_DIR}
)

# Qt-версия Snake (s21_snake_desktop)
add_executable(${SNAKE_DESKTOP_EXEC}
    ${GUI_DESKTOP_SOURCES}
    ${GUI_COMMON_SOURCES}
)
target_include_directories(${SNAKE_DESKTOP_EXEC} PRIVATE
    ${GUI_DESKTOP_DIR}
    ${GUI_COMMON_DIR}
    ${SNAKE_SRC_DIR}
    ${CMAKE_SOURCE_DIR}/brick_game/spec
)
target_link_libraries(${SNAKE_DESKTOP_EXEC} PRIVATE
    snake_lib
    Qt5::Widgets
)
set_target_properties(${SNAKE_DESKTOP_EXEC} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SNAKE_BIN_DIR}
)

# CLI-версия Snake (s21_snake_cli) с ncurses
add_executable(${SNAKE_CLI_EXEC}
    ${GUI_CLI_SOURCES}
)
target_include_directories(${SNAKE_CLI_EXEC} PRIVATE
    ${GUI_CLI_DIR}
    ${SNAKE_SRC_DIR}
)
target_link_libraries(${SNAKE_CLI_EXEC} PRIVATE
    snake_lib
    ncurses
)
set_target_properties(${SNAKE_CLI_EXEC} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SNAKE_BIN_DIR}
    OBJECT_OUTPUT_DIRECTORY ${OBJ_CLI_DIR}
)

# Qt-версия Tetris (s21_tetris_desktop)
add_executable(${TETRIS_DESKTOP_EXEC}
    ${GUI_DESKTOP_SOURCES}
    ${GUI_COMMON_SOURCES}
)
target_include_directories(${TETRIS_DESKTOP_EXEC} PRIVATE
    ${GUI_DESKTOP_DIR}
    ${GUI_COMMON_DIR}
    ${TETRIS_SRC_DIR}
    ${CMAKE_SOURCE_DIR}/brick_game/spec
)
target_link_libraries(${TETRIS_DESKTOP_EXEC} PRIVATE
    tetris_lib
    Qt5::Widgets
)
set_target_properties(${TETRIS_DESKTOP_EXEC} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TETRIS_BIN_DIR}
)

# CLI-версия Tetris (s21_tetris_cli) с ncurses
add_executable(${TETRIS_CLI_EXEC}
    ${GUI_CLI_SOURCES}
)
target_include_directories(${TETRIS_CLI_EXEC} PRIVATE
    ${GUI_CLI_DIR}
    ${TETRIS_SRC_DIR}
)
target_link_libraries(${TETRIS_CLI_EXEC} PRIVATE
    tetris_lib
    ncurses
)
set_target_properties(${TETRIS_CLI_EXEC} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TETRIS_BIN_DIR}
    OBJECT_OUTPUT_DIRECTORY ${OBJ_CLI_DIR}
)
