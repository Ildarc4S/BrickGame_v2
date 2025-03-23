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

# Поиск GTest
find_package(GTest REQUIRED)

set(SNAKE_SRC_DIR ${CMAKE_SOURCE_DIR}/brick_game/snake)
set(TETRIS_SRC_DIR ${CMAKE_SOURCE_DIR}/brick_game/tetris)
set(GUI_CLI_DIR ${CMAKE_SOURCE_DIR}/gui/cli)
set(GUI_DESKTOP_DIR ${CMAKE_SOURCE_DIR}/gui/desktop)
set(GUI_COMMON_DIR ${CMAKE_SOURCE_DIR}/gui/common)
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(OBJ_SNAKE_DIR ${BUILD_DIR}/obj/snake)
set(OBJ_TETRIS_DIR ${BUILD_DIR}/obj/tetris)
set(OBJ_CLI_DIR ${BUILD_DIR}/obj/cli)
set(SNAKE_BIN_DIR ${CMAKE_SOURCE_DIR}/bin/snake)
set(TETRIS_BIN_DIR ${CMAKE_SOURCE_DIR}/bin/tetris)
set(TEST_BIN_DIR ${CMAKE_SOURCE_DIR}/bin/tests)
set(COV_BIN_DIR ${CMAKE_SOURCE_DIR}/bin/coverage)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(COV_DIR ${CMAKE_SOURCE_DIR}/coverage/snake)

set(SNAKE_LIB_NAME s21_snake)
set(TETRIS_LIB_NAME s21_tetris)
set(SNAKE_DESKTOP_EXEC s21_snake_desktop)
set(SNAKE_CLI_EXEC s21_snake_cli)
set(TETRIS_DESKTOP_EXEC s21_tetris_desktop)
set(TETRIS_CLI_EXEC s21_tetris_cli)
set(SNAKE_TEST_EXEC s21_snake_test)
set(SNAKE_COV_EXEC s21_snake_coverage)

# Создание директорий
file(MAKE_DIRECTORY ${LIB_DIR})
file(MAKE_DIRECTORY ${SNAKE_BIN_DIR})
file(MAKE_DIRECTORY ${TETRIS_BIN_DIR})
file(MAKE_DIRECTORY ${OBJ_SNAKE_DIR})
file(MAKE_DIRECTORY ${OBJ_TETRIS_DIR})
file(MAKE_DIRECTORY ${OBJ_CLI_DIR})
file(MAKE_DIRECTORY ${TEST_BIN_DIR})
file(MAKE_DIRECTORY ${COV_BIN_DIR})
file(MAKE_DIRECTORY ${COV_DIR})

# Поиск исходных файлов
file(GLOB SNAKE_SOURCES "${SNAKE_SRC_DIR}/*.cpp")
file(GLOB TETRIS_SOURCES "${TETRIS_SRC_DIR}/*.cpp")
file(GLOB GUI_CLI_SOURCES "${GUI_CLI_DIR}/*.c")
file(GLOB GUI_DESKTOP_SOURCES "${GUI_DESKTOP_DIR}/*.cpp")
file(GLOB GUI_COMMON_SOURCES "${GUI_COMMON_DIR}/*.cpp")
file(GLOB SNAKE_TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/snake_tests/*.cc")

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

# CLI-версия Tetris (s21_tetris_cli) через Makefile
add_custom_target(${TETRIS_CLI_EXEC}
    COMMAND make s21_tetris_cli
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building s21_tetris_cli using Makefile"
    DEPENDS tetris_lib
)

# Тесты для Snake с GTest
add_executable(${SNAKE_TEST_EXEC}
    ${SNAKE_TEST_SOURCES}
)
target_include_directories(${SNAKE_TEST_EXEC} PRIVATE
    ${SNAKE_SRC_DIR}
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(${SNAKE_TEST_EXEC} PRIVATE
    snake_lib
    GTest::GTest
    GTest::Main
)
set_target_properties(${SNAKE_TEST_EXEC} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_BIN_DIR}
)

# Покрытие для Snake
add_executable(${SNAKE_COV_EXEC}
    ${SNAKE_TEST_SOURCES}
    ${SNAKE_SOURCES}
)
target_include_directories(${SNAKE_COV_EXEC} PRIVATE
    ${SNAKE_SRC_DIR}
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(${SNAKE_COV_EXEC} PRIVATE
    GTest::GTest
    GTest::Main
    gcov
)
target_compile_options(${SNAKE_COV_EXEC} PRIVATE --coverage)
target_link_options(${SNAKE_COV_EXEC} PRIVATE --coverage)
set_target_properties(${SNAKE_COV_EXEC} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${COV_BIN_DIR}
)


install(TARGETS ${SNAKE_DESKTOP_EXEC} ${SNAKE_CLI_EXEC} ${TETRIS_DESKTOP_EXEC}
    RUNTIME DESTINATION /usr/local/bin
)
install(FILES ${LIB_DIR}/${SNAKE_LIB_NAME}.a ${LIB_DIR}/${TETRIS_LIB_NAME}.a
    DESTINATION /usr/local/lib
)
install(CODE "execute_process(
    COMMAND make install
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE MAKE_INSTALL_RESULT
    )
    if(NOT MAKE_INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR \"Failed to run 'make install' for s21_tetris_cli\")
    endif()"
)

# Цель uninstall
add_custom_target(uninstall
    COMMAND rm -f /usr/local/bin/${SNAKE_DESKTOP_EXEC}
    COMMAND rm -f /usr/local/bin/${SNAKE_CLI_EXEC}
    COMMAND rm -f /usr/local/bin/${TETRIS_DESKTOP_EXEC}
    COMMAND rm -rf /usr/local/lib/${SNAKE_LIB_NAME}.a
    COMMAND rm -rf /usr/local/lib/${TETRIS_LIB_NAME}.a
    COMMAND make uninstall
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Uninstalling project files including s21_tetris_cli via Makefile"
)

# Цель dvi
add_custom_target(dvi
    COMMAND doxygen Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating documentation with Doxygen"
)

# Цель dist
add_custom_target(dist
    COMMAND ${CMAKE_COMMAND} -E make_directory package
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SNAKE_SRC_DIR} package/brick_game/snake
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${TETRIS_SRC_DIR} package/brick_game/tetris
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${GUI_CLI_DIR} package/gui/cli
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${GUI_DESKTOP_DIR} package/gui/desktop
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${GUI_COMMON_DIR} package/gui/common
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeLists.txt package/
    COMMAND tar -czvf s21_brickgame.tar.gz package
    COMMAND ${CMAKE_COMMAND} -E remove_directory package
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Creating distribution tarball"
)

# Цель test
add_custom_target(test
    COMMAND ${TEST_BIN_DIR}/${SNAKE_TEST_EXEC}
    DEPENDS ${SNAKE_TEST_EXEC}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running tests for Snake"
)

# Цель gcov_report
add_custom_target(gcov_report
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/*.gcda
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/*.gcno
    COMMAND ${COV_BIN_DIR}/${SNAKE_COV_EXEC}
    COMMAND lcov --capture --directory ${CMAKE_BINARY_DIR} --output-file ${COV_DIR}/coverage.info --ignore-errors inconsistent
    COMMAND lcov --remove ${COV_DIR}/coverage.info "/usr/include/*" "/usr/src/*" -o ${COV_DIR}/coverage.info --ignore-errors unused
    COMMAND genhtml ${COV_DIR}/coverage.info --output-directory ${COV_DIR}
    DEPENDS ${SNAKE_COV_EXEC}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating coverage report for Snake"
)

set_directory_properties(PROPERTIES
    ADDITIONAL_CLEAN_FILES
    "${SNAKE_BIN_DIR};${TETRIS_BIN_DIR};${BUILD_DIR};${LIB_DIR};${TEST_BIN_DIR};${COV_BIN_DIR};${COV_DIR};${CMAKE_SOURCE_DIR}/*.tar.gz;${CMAKE_SOURCE_DIR}/*.gcda;${CMAKE_SOURCE_DIR}/*.gcno"
)
