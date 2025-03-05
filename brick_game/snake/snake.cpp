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

void Snake::move() {
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
  body_.erase(body_.begin());
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

void SnakeGame::moveHandle(Direction direction, bool hold) {
  snake_.setDirection(direction);
  snake_.move();

  if (isCollide()) {
    state_ = State::GAME_OVER;
  }
}

}  // namespace s21

