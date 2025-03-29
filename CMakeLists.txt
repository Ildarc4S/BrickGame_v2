cmake_minimum_required(VERSION 3.16)
project(BrickGame LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

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
set(DOCS_DIR ${CMAKE_SOURCE_DIR}/docs/snake)

set(SNAKE_LIB_NAME s21_snake)
set(TETRIS_LIB_NAME s21_tetris)
set(SNAKE_DESKTOP_EXEC s21_snake_desktop)
set(SNAKE_CLI_EXEC s21_snake_cli)
set(TETRIS_DESKTOP_EXEC s21_tetris_desktop)
set(TETRIS_CLI_EXEC s21_tetris_cli)
set(SNAKE_TEST_EXEC s21_snake_test)
set(SNAKE_COV_EXEC s21_snake_coverage)
set(SNAKE_ARCHIVE_NAME "s21_brick_game.tar.gz")
set(SNAKE_ARCHIVE_PATH "${CMAKE_SOURCE_DIR}/${SNAKE_ARCHIVE_NAME}")

set(SNAKE_DESKTOP_HEADERS 
    ${GUI_DESKTOP_DIR}/include/window.h
    ${GUI_DESKTOP_DIR}/include/menu.h
    ${GUI_DESKTOP_DIR}/include/field_widget.h
    ${GUI_DESKTOP_DIR}/include/color_convert.h
    ${GUI_DESKTOP_DIR}/include/window_defines.h
    ${GUI_DESKTOP_DIR}/include/objects_code.h
)

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
file(GLOB SNAKE_SOURCES "${SNAKE_SRC_DIR}/*.cc")
file(GLOB TETRIS_SOURCES "${TETRIS_SRC_DIR}/*.cc")
file(GLOB GUI_CLI_SOURCES "${GUI_CLI_DIR}/*.c")
file(GLOB GUI_DESKTOP_SOURCES "${GUI_DESKTOP_DIR}/*.cc")
file(GLOB GUI_COMMON_SOURCES "${GUI_COMMON_DIR}/*.cc")
file(GLOB SNAKE_TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/snake_tests/*.cc")

add_library(snake_lib STATIC ${SNAKE_SOURCES})
set_target_properties(snake_lib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}
    OUTPUT_NAME ${SNAKE_LIB_NAME}
    PREFIX ""
    OBJECT_OUTPUT_DIRECTORY ${OBJ_SNAKE_DIR}
)
target_include_directories(snake_lib PUBLIC ${SNAKE_SRC_DIR})

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
    ${SNAKE_DESKTOP_HEADERS}
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
    ${SNAKE_DESKTOP_HEADERS}
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

add_custom_target(${TETRIS_CLI_EXEC}
    COMMAND make s21_tetris_cli
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    BYPRODUCTS ${TETRIS_BIN_DIR}/${TETRIS_CLI_EXEC}
    COMMENT "Building s21_tetris_cli using existing Makefile"
    DEPENDS tetris_lib
)

# Тесты для Snake с GTest
add_executable(${SNAKE_TEST_EXEC}
    ${SNAKE_SOURCES}
    ${SNAKE_TEST_SOURCES}
)
target_include_directories(${SNAKE_TEST_EXEC} PRIVATE
    ${SNAKE_SRC_DIR}
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(${SNAKE_TEST_EXEC} PRIVATE
    GTest::GTest
    GTest::Main
)
target_compile_definitions(${SNAKE_TEST_EXEC} PRIVATE SNAKE_TEST)
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
target_compile_definitions(${SNAKE_COV_EXEC} PRIVATE SNAKE_TEST)
target_compile_options(${SNAKE_COV_EXEC} PRIVATE --coverage)
target_link_options(${SNAKE_COV_EXEC} PRIVATE --coverage)
set_target_properties(${SNAKE_COV_EXEC} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${COV_BIN_DIR}
)

# Цель install
install(CODE "
    # 1. Устанавливаем Tetris через Makefile
    message(STATUS \"Installing Tetris via Makefile...\")
    execute_process(
        COMMAND make install
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE MAKE_INSTALL_RESULT
    )
    if(NOT MAKE_INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR \"Failed to install Tetris via Makefile\")
    endif()

    # 2. Генерируем документацию
    message(STATUS \"Generating documentation...\")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build . --target doc
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE DOC_RESULT
    )
    if(NOT DOC_RESULT EQUAL 0)
        message(WARNING \"Documentation generation failed\")
    endif()

    # 3. Устанавливаем документацию
    if(EXISTS \"${DOCS_DIR}/html\")
        file(INSTALL \"${DOCS_DIR}/html/\"
            DESTINATION /usr/local/share/doc/s21_snake
            PATTERN \".*\" EXCLUDE
        )
        message(STATUS \"Documentation installed to /usr/local/share/doc/s21_snake\")
    else()
        message(WARNING \"No documentation found to install\")
    endif()

    # 4. Устанавливаем компоненты Snake
    message(STATUS \"Installing Snake components...\")
"
    COMPONENT snake
)

# Установка исполняемых файлов и библиотек Snake
install(TARGETS ${SNAKE_DESKTOP_EXEC} ${SNAKE_CLI_EXEC}
    RUNTIME DESTINATION /usr/local/bin
    COMPONENT snake
)

install(FILES ${LIB_DIR}/${SNAKE_LIB_NAME}.a
    DESTINATION /usr/local/lib
    COMPONENT snake
)


# Цель uninstall
add_custom_target(uninstall
    COMMAND rm -f /usr/local/bin/${SNAKE_DESKTOP_EXEC}
    COMMAND rm -f /usr/local/bin/${SNAKE_CLI_EXEC}
    COMMAND rm -f /usr/local/bin/${TETRIS_DESKTOP_EXEC}
    COMMAND rm -rf /usr/local/lib/${SNAKE_LIB_NAME}.a
    COMMAND rm -rf /usr/local/lib/${TETRIS_LIB_NAME}.a
    COMMAND rm -rf /usr/local/share/doc/s21_snake
    COMMAND make uninstall
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Uninstalling project files including documentation and s21_tetris_cli"
)

# Цель dvi
add_custom_target(doc
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DOCS_DIR}
    COMMAND doxygen snake_doxy
    COMMAND make dvi
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating documentation with Doxygen in ${DOCS_DIR}"
)

add_custom_target(dvi DEPENDS doc)

# Цель dist
add_custom_target(dist
    COMMAND ${CMAKE_COMMAND} -E make_directory package
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SNAKE_SRC_DIR} package/brick_game/snake
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${TETRIS_SRC_DIR} package/brick_game/tetris
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${GUI_CLI_DIR} package/gui/cli
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${GUI_DESKTOP_DIR} package/gui/desktop
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${GUI_COMMON_DIR} package/gui/common
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeLists.txt package/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Makefile package/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/snake_readme.md package/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/tetris_readme.md package/
    COMMAND tar -czvf ${SNAKE_ARCHIVE_PATH} package
    COMMAND make dist
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
    "${SNAKE_BIN_DIR};${TETRIS_BIN_DIR};${BUILD_DIR};${LIB_DIR};${TEST_BIN_DIR};${COV_BIN_DIR};${COV_DIR};${DOCS_DIR};${DOCS_OUTPUT_DIR};${SNAKE_ARCHIVE_PATH};${CMAKE_SOURCE_DIR}/*.gcda;${CMAKE_SOURCE_DIR}/*.gcno"
)

# Цели для форматирования кода
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(clang_test
        COMMAND ${CLANG_FORMAT} --style=Google --dry-run --Werror ${SNAKE_SOURCES} ${TETRIS_SOURCES} ${GUI_CLI_SOURCES} ${GUI_DESKTOP_SOURCES} ${GUI_COMMON_SOURCES} ${SNAKE_TEST_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Checking code style with clang-format"
    )

    add_custom_target(clang_format
        COMMAND ${CLANG_FORMAT} --style=Google -i ${SNAKE_SOURCES} ${TETRIS_SOURCES} ${GUI_CLI_SOURCES} ${GUI_DESKTOP_SOURCES} ${GUI_COMMON_SOURCES} ${SNAKE_TEST_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Formatting code with clang-format"
    )
else()
    message(WARNING "clang-format not found - clang_format and clang_test targets will not be available")
endif()

# Цель для проверка утечки памяти
find_program(VALGRIND "valgrind")
if(VALGRIND)
    add_custom_target(valgrind_test
        COMMAND ${VALGRIND} --leak-check=full --track-origins=yes --show-leak-kinds=all --error-exitcode=1 ${TEST_BIN_DIR}/${SNAKE_TEST_EXEC}
        DEPENDS ${SNAKE_TEST_EXEC}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running memory leak check with valgrind"
    )
else()
    message(WARNING "valgrind not found - valgrind_test targets will not be available")
endif()
