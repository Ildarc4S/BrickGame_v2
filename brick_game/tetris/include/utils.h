/**
 * @file utils.h
 * @brief Вспомогательные функции для игры Тетрис
 */

#ifndef UTILS_H
#define UTILS_H

#include "./tetris.h"

#define UTILS_ERROR -1       ///< Код ошибки
#define UTILS_NOT_COLLIDE 0  ///< Код отсутствия коллизии

/**
 * @brief Очищает игровое поле
 * @param field Двумерный массив поля
 */
void clearField(int** field);

/**
 * @brief Удаляет текущую фигуру с поля
 * @param tetris Указатель на объект игры
 */
void clearTetraminoFromField(Tetris_t* tetris);

/**
 * @brief Проверяет коллизию фигуры
 * @param tetris Указатель на объект игры
 * @param tetramino Указатель на фигуру
 * @return Код коллизии (0 - нет, 1 - есть, -1 - ошибка)
 */
int isCollide(Tetris_t *tetris, Tetramino_t *tetramino);

/**
 * @brief Заменяет текущую фигуру
 * @param self Указатель на объект игры
 * @param tetramino Указатель на новую фигуру
 */
void replaceTetramino(Tetris_t *self, Tetramino_t *tetramino);

/**
 * @brief Вставляет фигуру в поле (как часть стены)
 * @param self Указатель на объект игры
 */
void insertTetraminoToField(Tetris_t *self);

/**
 * @brief Копирует матрицу фигуры
 * @param brick_one Матрица назначения
 * @param brick_two Матрица источника
 */
void copyTetramino(int brick_one[TETRAMINO_HEIGHT][TETRAMINO_WIDTH],
                   int brick_two[TETRAMINO_HEIGHT][TETRAMINO_WIDTH]);

/**
 * @brief Копирует фигуру в текущую фигуру игры
 * @param tetris Указатель на объект игры
 * @param tetramino Указатель на фигуру для копирования
 */
void copyTetraminoToCurrentTetramino(Tetris_t *tetris, Tetramino_t *tetramino);

/**
 * @brief Поворачивает фигуру на 90 градусов
 * @param tetramino Указатель на фигуру
 */
void rotateTetramino(Tetramino_t *tetramino);

/**
 * @brief Сдвигает линии вниз после очистки
 * @param self Указатель на объект игры
 * @param index Указатель на индекс линии
 */
void shiftLines(Tetris_t *self, int *index);

/**
 * @brief Очищает заполненные линии
 * @param self Указатель на объект игры
 */
void clearLines(Tetris_t *self);

/**
 * @brief Двигает фигуру горизонтально
 * @param tetris Указатель на объект игры
 * @param direction Направление движения (-1 влево, 1 вправо)
 */
void moveHorizontal(Tetris_t* tetris, int direction);

/**
 * @brief Вставляет фигуру в поле с учетом цвета
 * @param self Указатель на объект игры
 */
void insertTetraminoToFieldWithColor(Tetris_t *self);

#endif  // UTILS_H

