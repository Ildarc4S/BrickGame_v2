/**
 * @file game_manager.cc
 * @brief Реализация логики игры Snake
 * @details Содержит реализацию всех методов класса SnakeGame для управления:
 * - Состояниями игры (старт, пауза, завершение)
 * - Движением и ростом змейки
 * - Генерацией яблок
 * - Обработкой столкновений
 * - Управлением таймером и скоростью
 * - Работой с рекордами
 */

#include "./include/game_manager.h"

namespace s21 {

/**
 * @brief Конструктор инициализирует игровые параметры
 * @details Создает игровое поле, устанавливает начальные значения:
 * - Таймер с начальным интервалом
 * - Змейку в стартовой позиции
 * - Яблоко в случайной позиции
 * - Параметры скорости и счета
 */
SnakeGame::SnakeGame()
    : state_(State::kStart),
      action_(UserAction_t::Start),
      timer_(INITIAL_TIMER),
      snake_(),
      apple_(snake_.getBody()),
      db_("snake_db.txt"),
      boost_time_(false) {
  game_info_.field = MemoryUtility::createField(FIELD_WIDTH + FIELD_BORDER,
                                                FIELD_HEIGHT + FIELD_BORDER);
  game_info_.next = nullptr;
  game_info_.score = INITIAL_SCORE;
  game_info_.high_score = INITIAL_SCORE;
  game_info_.level = INITIAL_LEVEL;
  game_info_.speed = INITIAL_SPEED;
  game_info_.pause = static_cast<int>(PauseMode::kStart);

  max_level_score_ = LEVEL_SCORE_THRESHOLD;
  max_level_ = MAX_LEVEL;
  add_score_ = SCORE_INCREMENT;
  max_score_ = MAX_SCORE;
  interval_diff_ = INTERVAL_DECREMENT;
  interval_boost_diff_ = BOOST_INTERVAL_DIVISOR;
}

/**
 * @brief Деструктор освобождает ресурсы
 * @details Удаляет динамически выделенную память для игрового поля
 */
SnakeGame::~SnakeGame() {
  MemoryUtility::removeField(game_info_.field, FIELD_HEIGHT + FIELD_BORDER);
}

/**
 * @brief Обрабатывает действия в начальном состоянии
 */
void SnakeGame::startHandler(UserAction_t action) {
  switch (action) {
    case Start:
      start();
      break;
    case Terminate:
      exit();
      break;
    default:
      break;
  }
}

/**
 * @brief Переключает режим ускорения игры
 * @details Уменьшает/восстанавливает интервал таймера вдвое
 */
void SnakeGame::toogleBoostTime() {
  boost_time_ = !boost_time_;
  if (boost_time_) {
    timer_.setInterval(timer_.getInterval() / interval_boost_diff_, true);
  } else {
    timer_.setInterval(timer_.getLastInterval(), false);
  }
}

/**
 * @brief Обрабатывает движение змейки
 */
void SnakeGame::moveHandler(UserAction_t action, bool hold) {
  switch (action) {
    case Terminate:
      exit();
      break;
    case Pause:
      pause();
      break;
    case Left:
      moveHandle(Direction::kLeft, hold);
      break;
    case Right:
      moveHandle(Direction::kRight, hold);
      break;
    case Up:
      moveHandle(Direction::kUp, hold);
      break;
    case Down:
      moveHandle(Direction::kDown, hold);
      break;
    case Action:
      toogleBoostTime();
    default:
      break;
  }
}

/**
 * @brief Обрабатывает паузу игры
 * @param action Действие пользователя
 */
void SnakeGame::pauseHandler(UserAction_t action) {
  switch (action) {
    case Terminate:
      exit();
      break;
    case Start:
      start();
      break;
    default:
      break;
  }
}

/**
 * @brief Обрабатывает завершение игры
 * @param action Действие пользователя
 */
void SnakeGame::gameOverHandler(UserAction_t action) {
  switch (action) {
    case Start:
      start();
      break;
    case Terminate:
      exit();
      break;
    default:
      break;
  }
}

/**
 * @brief Основной обработчик пользовательского ввода
 * @param action Действие пользователя
 * @param hold Флаг удержания клавиши
 */
void SnakeGame::userInput(UserAction_t action, bool hold) {
  switch (state_) {
    case State::kStart:
      startHandler(action);
      break;
    case State::kMove:
      moveHandler(action, hold);
      break;
    case State::kPause:
      pauseHandler(action);
      break;
    case State::kGameOver:
      gameOverHandler(action);
      break;
    default:
      break;
  }
}

/**
 * @brief Запускает новую игру
 * @details В зависимости от текущего состояния:
 * - При старте создает новую игру
 * - При паузе продолжает игру
 * - При завершении сбрасывает параметры
 */
void SnakeGame::start() {
  if (state_ == State::kStart) {
    spawn();
    game_info_.high_score = db_.read();
  } else if (state_ == State::kPause) {
    state_ = State::kMove;
  } else if (state_ == State::kGameOver) {
    game_info_.high_score = db_.read();
    if (game_info_.score >= game_info_.high_score) {
      game_info_.high_score = game_info_.score;
      db_.write(game_info_.high_score);
    }
    game_info_.level = INITIAL_LEVEL;
    game_info_.score = INITIAL_SCORE;
    game_info_.speed = INITIAL_SPEED;
    timer_.resetInterval();
    spawn();
  }
  game_info_.pause = static_cast<int>(PauseMode::kGameContinue);
}

/**
 * @brief Генерирует начальные позиции змейки и яблока
 */
void SnakeGame::spawn() {
  snake_ = Snake();
  state_ = State::kMove;
}

/**
 * @brief Ставит игру на паузу
 */
void SnakeGame::pause() {
  game_info_.pause = static_cast<int>(PauseMode::kPause);
  state_ = State::kPause;
}

/**
 * @brief Завершает игру с сохранением рекорда
 */
void SnakeGame::exit() {
  db_.write(game_info_.high_score);
  game_info_.pause = static_cast<int>(PauseMode::kExit);
  state_ = State::kExit;

  game_info_.high_score = db_.read();
  if (game_info_.score >= game_info_.high_score) {
    game_info_.high_score = game_info_.score;
    db_.write(game_info_.high_score);
  }
}

/**
 * @brief Обрабатывает съедание яблока
 * @details Увеличивает счет, генерирует новое яблоко,
 * проверяет переход на новый уровень и победу
 */
void SnakeGame::eat() {
  game_info_.score += add_score_;
  apple_.genRandPosition(snake_.getBody());
  state_ = State::kMove;

  int new_level = game_info_.score / max_level_score_ + 1;
  if (new_level > game_info_.level) {
    timer_.setInterval(timer_.getLastInterval() - interval_diff_, true);
    timer_.updateLastinterval();
    game_info_.level = new_level;
    game_info_.speed += add_speed_;
  }

  if (game_info_.level > max_level_) {
    game_info_.level = max_level_;
  }

  if (game_info_.score >= max_score_) {
    state_ = State::kGameOver;
    game_info_.pause = static_cast<int>(PauseMode::kWin);
  }
}

/**
 * @brief Проверяет столкновение головы с яблоком
 * @param head Позиция головы змейки
 * @return true если голова достигла яблока
 */
bool SnakeGame::isAppleCollide(const Point& head) {
  return head == apple_.getPosition();
}

/**
 * @brief Проверяет столкновение с границами или телом
 * @param new_head Новая позиция головы
 * @return true если обнаружено столкновение
 */
bool SnakeGame::isCollision(const Point& new_head) {
  bool result = false;
  if (new_head.getX() <= 0 || new_head.getX() >= FIELD_WIDTH + 1 ||
      new_head.getY() <= 0 || new_head.getY() >= FIELD_HEIGHT + 1) {
    result = true;
  }

  const std::vector<Point>& snake_body = snake_.getBody();
  for (size_t i = 0; i < snake_body.size() - 1 && !result; i++) {
    if (new_head == snake_body[i]) {
      result = true;
    }
  }

  return result;
}

/**
 * @brief Проверяет противоположное направление
 * @param direction Проверяемое направление
 * @return true если направление противоположно текущему
 */
bool SnakeGame::isOppositeDirection(const Direction& direction) {
  bool result = false;
  Direction currentDirection = snake_.getDirection();

  if ((currentDirection == Direction::kRight &&
       direction == Direction::kLeft) ||
      (currentDirection == Direction::kLeft &&
       direction == Direction::kRight) ||
      (currentDirection == Direction::kUp && direction == Direction::kDown) ||
      (currentDirection == Direction::kDown && direction == Direction::kUp)) {
    result = true;
  }

  return result;
}

/**
 * @brief Обрабатывает движение змейки
 * @param direction Направление движения
 * @param hold Флаг удержания клавиши
 */
void SnakeGame::moveHandle(Direction direction, bool hold) {
  if (isOppositeDirection(direction)) {
    return;
  }
  (void)hold;

  snake_.setDirection(direction);
  Point new_head = snake_.calcAndGetNewHeadPos();

  if (isCollision(new_head)) {
    state_ = State::kGameOver;
    game_info_.pause = static_cast<int>(PauseMode::kGameOver);
  } else {
    bool is_colide_apple = isAppleCollide(new_head);
    snake_.move(is_colide_apple);
    timer_.update();

    if (is_colide_apple) {
      eat();
    }
  }
}

/**
 * @brief Очищает игровое поле
 * @param width Ширина поля
 * @param height Высота поля
 */
void SnakeGame::clearField(int width, int height) {
  if (game_info_.field == nullptr) return;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
        game_info_.field[i][j] = static_cast<int>(FigureCode::kWall);
      } else {
        game_info_.field[i][j] = static_cast<int>(FigureCode::kAir);
      }
    }
  }
}

/**
 * @brief Возвращает текущее состояние игры
 * @return Структура GameInfo_t с актуальными данными
 * @details Обновляет игровое поле перед возвратом:
 * - Очищает поле
 * - Размещает границы
 * - Добавляет яблоко и змейку
 * - Обрабатывает автоматическое движение
 */
GameInfo_t SnakeGame::getGameInfo() {
  if (state_ == State::kMove && timer_.isExpired() &&
      game_info_.field != nullptr) {
    moveHandle(snake_.getDirection(), false);
  }

  if (game_info_.field != nullptr) {
    clearField(FIELD_WIDTH + FIELD_BORDER, FIELD_HEIGHT + FIELD_BORDER);
    const Point& apple_position = apple_.getPosition();
    game_info_.field[apple_position.getY()][apple_position.getX()] =
        static_cast<int>(FigureCode::kApple);

    for (const auto& elm : snake_.getBody()) {
      game_info_.field[elm.getY()][elm.getX()] =
          static_cast<int>(FigureCode::kSnake);
    }
  }

  return game_info_;
}

}  // namespace s21
