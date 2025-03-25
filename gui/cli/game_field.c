#include "./include/game_field.h"

void drawCleanField(GameField_t *self) {
    for (int i = 0; i < self->height; i++) {
        for (int j = 0; j < self->width; j++) {
            if (i == self->height - 1 || j == self->width - 1 || i == 0 || j == 0) {
                mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "[]");
            } else {
                mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "  ");
            }
        }
    }
}

bool isTetraminoCode(int field_code) {
    return field_code == OBJECT_CODE_TETRAMINO_I
           || field_code == OBJECT_CODE_TETRAMINO_O
           || field_code == OBJECT_CODE_TETRAMINO_T
           || field_code == OBJECT_CODE_TETRAMINO_S
           || field_code == OBJECT_CODE_TETRAMINO_Z
           || field_code == OBJECT_CODE_TETRAMINO_J
           || field_code == OBJECT_CODE_TETRAMINO_L;
}

void _drawField(GameField_t *self) {
    GameInfo_t game = updateCurrentState();

    for (int i = 0; i < self->height; i++) {
        for (int j = 0; j < self->width; j++) {
            mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "  ");
        }
    }

    if (game.pause == PAUSE_MODE_GAME_CONTINUE) {
        for (int i = 0; i < self->height; i++) {
            for (int j = 0; j < self->width; j++) {
                if (game.field[i][j] == OBJECT_CODE_WALL) {
                    mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "[]");
                } else if (isTetraminoCode(game.field[i][j]) || game.field[i][j] == OBJECT_CODE_SNAKE) {
                    attron(COLOR_PAIR(game.field[i][j]));
                    mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "[]");
                    attroff(COLOR_PAIR(game.field[i][j]));
                } else if (game.field[i][j] == OBJECT_CODE_AIR) {
                    mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "  ");
                } else if (game.field[i][j] == OBJECT_CODE_APPLE) {
                    attron(COLOR_PAIR(game.field[i][j]));
                    mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "()");
                    attroff(COLOR_PAIR(game.field[i][j]));
                }
            }
        }
    } else if (game.pause == PAUSE_MODE_START) {
        drawCleanField(self);
        mvprintw(self->height / GAME_FIELD_CENTER_DIVISOR, ((self->width - GAME_FIELD_CENTER_OFFSET) / GAME_FIELD_CENTER_DIVISOR) * GAME_FIELD_CELL_WIDTH, "START");
    } else if (game.pause == PAUSE_MODE_PAUSE) {
        drawCleanField(self);
        mvprintw(self->height / GAME_FIELD_CENTER_DIVISOR, ((self->width - GAME_FIELD_CENTER_OFFSET) / GAME_FIELD_CENTER_DIVISOR) * GAME_FIELD_CELL_WIDTH, "PAUSE");
    } else if (game.pause == PAUSE_MODE_GAME_OVER) {
        drawCleanField(self);
        mvprintw(self->height / GAME_FIELD_CENTER_DIVISOR, ((self->width - GAME_FIELD_CENTER_OFFSET) / GAME_FIELD_CENTER_DIVISOR) * GAME_FIELD_CELL_WIDTH, "GAME_OVER");
    }
}

GameField_t initGameField(int width, int height) {
    return (GameField_t){
        .x = GAME_FIELD_GAME_FIELD_INIT_X,
        .y = GAME_FIELD_GAME_FIELD_INIT_Y,
        .width = width,
        .height = height,
        .drawField = _drawField,
    };
}
