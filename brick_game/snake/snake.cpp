#include "./include/snake.h"
#include <iostream>
#include <vector>

namespace s21 {

Snake::Snake()
  : direction_(Direction::RIGHT),
  speed_(1) {
    for (int i = 1; i < 5; ++i) {
      body_.emplace_back(i, 2);
    }
}

Direction Snake::getDirection() {
    return direction_;
}

const std::vector<Point>& Snake::getBody() const {
    return body_;
}

Point Snake::calcAndGetNewHeadPos() {
  Point new_head = body_.back();
  switch (direction_) {
    case Direction::RIGHT:
      new_head.setX()++;
      break;
    case Direction::DOWN:
      new_head.setY()++;
      break;
    case Direction::LEFT:
      new_head.setX()--;
      break;
    case Direction::UP:
      new_head.setY()--;
      break;
  }

  return new_head;
}

SnakeGame::SnakeGame()
  : state_(State::START),
    action_(UserAction_t::Start),
    snake_(),
    score_(0),
    db_("./brick_game/snake/db/score.txt"),
    pause_(false){
    game_info_.field = fillField(FIELD_WIDTH, FIELD_HEIGHT);
  apple_.genRandPosition(snake_.getBody());
}

int** SnakeGame::fillField(int width, int height) {
  int** ptr = new int*[height];
  for (int i = 0; i < height; i++) {
    ptr[i] = new int[width];
  }
  return ptr;
}

void Snake::move(bool apple_eat) {
  Point new_head = calcAndGetNewHeadPos();

  body_.push_back(new_head);

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
  bool result = false;
  const Point& temp = snake_.getBody().back();
  if (temp.getX() < 0 || temp.getY() < 0 ||
      temp.getX() >= FIELD_WIDTH-1 || temp.getY() >= FIELD_WIDTH-1) {
    result = true;
  }

  for (const auto& body_elm : snake_.getBody()) {
    if (temp == body_elm && temp != snake_.getBody().back()) {
      result = true;
    }
  }

  return result;
}

bool SnakeGame::isAppleCollide(const Point& head) {
  std::cout << "(" << head.getY() << " " << head.getX() << std::endl;
  std::cout << "(" << apple_.getPosition().getY() << " " << apple_.getPosition().getX() << std::endl;
  return head == apple_.getPosition();
}

void SnakeGame::moveHandle(Direction direction, bool hold) {
  snake_.setDirection(direction);
  Point new_head = snake_.calcAndGetNewHeadPos();

  bool is_colide_apple = isAppleCollide(new_head);
  snake_.move(is_colide_apple);
  std::cout << is_colide_apple;

  if (is_colide_apple) {
    std::cout << "EM";
    state_ = State::EAT;
  } else if (isCollide()) {
    state_ = State::GAME_OVER;
  }
}

void SnakeGame::clearField(int width, int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (i == 0 || j == 0 || i == height-1 || j == width-1) {
        game_info_.field[i][j] = static_cast<int>(FigureCode::WALL);
      } else {
        game_info_.field[i][j] = static_cast<int>(FigureCode::AIR);
      }
    }
  }
}

GameInfo_t SnakeGame::getGameInfo() {
  if (game_info_.field != nullptr) {
    clearField(FIELD_WIDTH, FIELD_HEIGHT);
    const Point& apple_position = apple_.getPosition();
    game_info_.field[apple_position.getY()][apple_position.getX()] = static_cast<int>(FigureCode::APPLE);

    for (const auto& elm : snake_.getBody()) {
      game_info_.field[elm.getY()][elm.getX()] = static_cast<int>(FigureCode::SNAKE);
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

