#include "./include/snake.h"
#include <iostream>
#include <vector>

namespace s21 {
Snake::Snake()
  : direction_(Direction::RIGHT),
  speed_(1) {
    for (int i = 0; i < 4; ++i) {
      body_.emplace_back(i, 0);
    }
}

Direction Snake::getDirection() {
    return direction_;
}

const std::vector<Point>& Snake::getBody() const {
    return body_;
}

int** SnakeGame::fillField(int width, int height) {
  int** ptr = new int*[height];
  for (int i = 0; i < height; i++) {
    ptr[i] = new int[width];
  }
  return ptr;
}

void Snake::move(bool apple_eat) {
  Point temp = body_.back();

  switch (direction_) {
    case Direction::RIGHT:
      temp.setX()++;
      break;
    case Direction::DOWN:
      temp.setY()++;
      break;
  }

  body_.push_back(temp);

  if (!apple_eat) {
    body_.erase(body_.begin());
  }
}

void SnakeGame::userInput(UserAction_t action, bool hold) {
  switch (state_) {
    case State::START:
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
      break;
    case State::EAT:
      eat();
      break;
    case State::MOVE:
      switch (action) {
        case Terminate:
          exit();
          break;
        case Pause:
          pause();
          break;
        case Left:
          moveHandle(Direction::LEFT, hold);
          break;
        case Right:
          moveHandle(Direction::RIGHT, hold);
          break;
        case Up:
          moveHandle(Direction::UP, hold);
          break;
        case Down:
          moveHandle(Direction::DOWN, hold);
          break;
        default:
          break;
      }
      break;
    case State::PAUSE:
      switch (action) {
        case Terminate:
          exit();
          break;
        case Start:
          start();
          break;
        case Pause:
          pause();
          break;

        default:
          break;
      }

      break;
    case State::GAME_OVER:
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
      break;

    default:
      break;
  }
  std::cout << (int)state_ << std::endl;
}

void SnakeGame::start() {
  if (state_ == State::START) {
    spawn();
    game_info_.high_score = db_.read();
  } else if (state_ == State::PAUSE) {
    state_ = State::MOVE;
  } else if (state_ == State::GAME_OVER) {
    // cleanField(game_info_.field);
    game_info_.level = 1;
    game_info_.score = 0;

    game_info_.speed = 10;
    spawn();
  }
  game_info_.pause = 0;
}

void SnakeGame::spawn() {
  if (state_ == State::EAT) {
    apple_.genRandPosition(snake_.getBody());
  } else if (state_ == State::START) {
    snake_ = Snake();
    std::cout << "Spawn";
    state_ = State::MOVE;
  }
}

void SnakeGame::pause() {
  game_info_.pause = (int)(PauseState::PAUSE);
  state_ = State::PAUSE;
}

void SnakeGame::exit() {
  db_.write(game_info_.high_score);
  state_ = State::EXIT;
}

void SnakeGame::eat() {
  game_info_.score += 10;
  apple_.genRandPosition(snake_.getBody());
  state_ = State::MOVE;
}

bool SnakeGame::isCollide() {
  bool result = true;
  const Point& temp = snake_.getBody().back();
  if (temp.getX() < 0 || temp.getY() < 0 ||
      temp.getX() >= FIELD_WIDTH || temp.getY() >= FIELD_WIDTH) {
    result = false;
  }

  for (const auto& body_elm : snake_.getBody()) {
    if (temp == body_elm) {
      result = false;
    }
  }

  return result;
}

bool SnakeGame::isAppleCollide() {
  return snake_.getBody().back() == apple_.getPosition();
}

void SnakeGame::moveHandle(Direction direction, bool hold) {
  std::cout << "Move\n" << snake_.getBody().back().getX() << "\n";
  snake_.setDirection(direction);
  snake_.move();

  if (isAppleCollide()) {
    state_ = State::EAT;
  }

  if (isCollide()) {
    state_ = State::GAME_OVER;
  }
}

void SnakeGame::clearField(int width, int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      game_info_.field[i][j] = 0; 
    }
  }
}  

GameInfo_t SnakeGame::getGameInfo() {
  if (game_info_.field != nullptr) {
    clearField(FIELD_WIDTH, FIELD_HEIGHT);
    for (const auto& elm : snake_.getBody()) {
      game_info_.field[elm.getY()][elm.getX()] = 2;
    }
  }

  return game_info_;
}

}  // namespace s21

void userInput(UserAction_t action, bool hold) {
  s21::SnakeGameSingleton::getSnakeGame().userInput(action, hold);
}

GameInfo_t updateCurrentState() {
  return s21::SnakeGameSingleton::getSnakeGame().getGameInfo();
}

