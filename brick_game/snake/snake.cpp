#include "./include/snake.h"
#include <vector>
#include <utility>

namespace s21 {

Snake::Snake()
  : direction_(Direction::RIGHT),
    body_(),
    speed_(1) {
  int mid_x = FIELD_WIDTH / 2;
  int mid_y = FIELD_HEIGHT / 2;

  for (int i = 0; i < 4; i++) {
    body_.emplace_back(mid_x + i, mid_y);
  }
}

Snake::Snake(const Snake& other)
  : direction_(other.direction_),
    body_(other.body_),
    speed_(other.speed_)
{}

Snake::Snake(Snake&& other)
  : direction_(std::move(other.direction_)),
    body_(std::move(other.body_)),
    speed_(std::move(other.speed_))
{}

Snake& Snake::operator=(const Snake& other) {
  if (this != &other) {
    direction_ = other.direction_;
    speed_ = other.speed_;
    body_ = other.body_;
  }
  return *this;
}

Snake& Snake::operator=(Snake&& other) {
  if (this != &other) {
    direction_ = std::move(other.direction_);
    speed_ = std::move(other.speed_);
    body_ = std::move(other.body_);
  }
  return *this;
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
    timer_(500),
    snake_(),
    apple_(snake_.getBody()),
    db_("snake_db.txt"),
    boost_time_(false){
    game_info_.field = MemoryUtility::createField(FIELD_WIDTH+2, FIELD_HEIGHT+2);
    game_info_.next = nullptr;
    game_info_.score = 0;
    game_info_.high_score = 0;
    game_info_.level = 1;
    game_info_.speed = 10;
    game_info_.pause = static_cast<int>(PauseMode::START);

    max_level_score_ = 5;
    max_level_ = 10;
    add_score_ = 1;
    max_score_ = 200;
    interval_diff_ = 50;
    interval_boost_diff_ = 80;
}

SnakeGame::~SnakeGame() {
  MemoryUtility::removeField(game_info_.field, FIELD_HEIGHT+2);
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
        case Action:
          boost_time_ = !boost_time_;
          if (boost_time_) {
            timer_.setInterval(timer_.getInterval() - interval_boost_diff_, /*save =*/ true);
          } else {
            timer_.setInterval(timer_.getLastInterval(), /*save =*/ false);
          }
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
    game_info_.high_score = db_.read();
    if (game_info_.score >= game_info_.high_score) {
      game_info_.high_score = game_info_.score;
      db_.write(game_info_.high_score);
    }
    game_info_.level = 1;
    game_info_.score = 0;
    game_info_.speed = 10;
    timer_.resetInterval();

    spawn();
  }
  game_info_.pause = static_cast<int>(PauseMode::GAME_CONTINUE);
}


void SnakeGame::spawn() {
  snake_ = Snake();
  state_ = State::MOVE;
}

void SnakeGame::pause() {
  game_info_.pause = static_cast<int>(PauseMode::PAUSE);
  state_ = State::PAUSE;
}

void SnakeGame::exit() {
  db_.write(game_info_.high_score);
  game_info_.pause = static_cast<int>(PauseMode::EXIT);
  state_ = State::EXIT;

  game_info_.high_score = db_.read();
  if (game_info_.score >= game_info_.high_score) {
    game_info_.high_score = game_info_.score;
    db_.write(game_info_.high_score);
  }
}

void SnakeGame::eat() {
  game_info_.score += add_score_;
  apple_.genRandPosition(snake_.getBody());
  state_ = State::MOVE;

  int new_level = game_info_.score / max_level_score_ + 1;
  if (new_level > game_info_.level) {
    timer_.setInterval(timer_.getLastInterval()-interval_diff_, /*save =*/ true);
    timer_.updateLastinterval();
    game_info_.level = new_level;
    game_info_.speed += add_speed_;
  }

  if (game_info_.level > max_level_) {
    game_info_.level = max_level_;
  }

  if (game_info_.score >= max_score_) {
    state_ = State::GAME_OVER;
    game_info_.pause = static_cast<int>(PauseMode::WIN);
  }
}

void SnakeGame::speedBoost() {
  boost_time_ = !boost_time_;
  if (boost_time_) {
    timer_.setInterval(timer_.getInterval() - 80, /*save =*/ true);
  } else {
    timer_.setInterval(timer_.getLastInterval(), /*save =*/ false);
  }
}

bool SnakeGame::isAppleCollide(const Point& head) {
  return head == apple_.getPosition();
}

bool SnakeGame::isCollision(const Point& new_head) {
  bool result = false;
  if (new_head.getX() <= 0 || new_head.getX() >= FIELD_WIDTH + 1
      || new_head.getY() <= 0 || new_head.getY() >= FIELD_HEIGHT + 1) {
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

bool SnakeGame::isOppositeDirection(const Direction& direction) {
  bool result = false;
  Direction currentDirection = snake_.getDirection();

  if ((currentDirection == Direction::RIGHT && direction == Direction::LEFT) ||
      (currentDirection == Direction::LEFT && direction == Direction::RIGHT) ||
      (currentDirection == Direction::UP && direction == Direction::DOWN) ||
      (currentDirection == Direction::DOWN && direction == Direction::UP)) {
    result = true;
  }

  return result;
}

void SnakeGame::moveHandle(Direction direction, bool hold) {
  if (isOppositeDirection(direction)) {
    return;
  }
  (void)hold;

  snake_.setDirection(direction);
  Point new_head = snake_.calcAndGetNewHeadPos();

  if (isCollision(new_head)) {
    state_ = State::GAME_OVER;
    game_info_.pause = static_cast<int>(PauseMode::GAME_OVER);
  } else {
    bool is_colide_apple = isAppleCollide(new_head);
    snake_.move(is_colide_apple);
    timer_.update();

    if (is_colide_apple) {
      eat();
    }
  }
}

void SnakeGame::clearField(int width, int height) {
  if (game_info_.field == nullptr) return;

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
  if (state_ == State::MOVE && timer_.isExpired() && game_info_.field != nullptr) {
    moveHandle(snake_.getDirection(), false);
  }

  if (game_info_.field != nullptr) {
    clearField(FIELD_WIDTH+2, FIELD_HEIGHT+2);
    const Point& apple_position = apple_.getPosition();
    game_info_.field[apple_position.getY()][apple_position.getX()] = static_cast<int>(FigureCode::APPLE);

    for (const auto& elm : snake_.getBody()) {
      game_info_.field[elm.getY()][elm.getX()] = static_cast<int>(FigureCode::SNAKE);
    }
  }

  return game_info_;
}

}  // namespace s21

extern "C" {
  void userInput(UserAction_t action, bool hold) {
    s21::SnakeGameSingleton::getSnakeGame().userInput(action, hold);
  }

  GameInfo_t updateCurrentState() {
    return s21::SnakeGameSingleton::getSnakeGame().getGameInfo();
  }
}

