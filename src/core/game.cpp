#include "core/game.h"

namespace tank_hero {

Game::Game(size_t window_width)
    : window_width_(window_width),
      tank_(vec2(window_width / 2, window_width / 2)),
      timer_(0) {
  timer_.start();
}

void Game::HandleTankMovement(const set<int>& keys) {
  bool a_pressed = false, s_pressed = false, d_pressed = false,
       w_pressed = false;
  for (int key : keys) {
    if (key == KeyEvent::KEY_a) a_pressed = true;
    if (key == KeyEvent::KEY_s) s_pressed = true;
    if (key == KeyEvent::KEY_d) d_pressed = true;
    if (key == KeyEvent::KEY_w) w_pressed = true;
  }

  if (w_pressed) tank_.MoveUp();
  if (a_pressed) tank_.MoveLeft();
  if (d_pressed) tank_.MoveRight();
  if (s_pressed) tank_.MoveDown();
  tank_.KeepInMap(kFieldWidth);
}

void Game::Update() {
  HandleBulletEnemyCollision();
  HandleTankEnemyCollision();
  RemoveInvalidBullets();
  RemoveDeadEnemies();

  for (Bullet& bullet : bullets_) {
    bullet.Move();
  }
  for (Enemy& enemy : enemies_) {
    enemy.Move();
  }
}

void Game::FireBullet(const vec2& mouse_pos) {
  if (TankIsLoaded()) bullets_.emplace_back(tank_, mouse_pos);
}

void Game::HandleBulletEnemyCollision() {
  for (Bullet& bullet : bullets_) {
    for (Enemy& enemy : enemies_) {
      if (bullet.DidHit(enemy)) {
        bullet.GoesInactive();
        enemy.Dies();
        kill_count_++;
      }
    }
  }
}

void Game::RemoveInvalidBullets() {
  bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
                                [](const Bullet& bullet) {
                                  return !bullet.IsActive() ||
                                         bullet.IsOutOfMap(kFieldWidth);
                                }),
                 bullets_.end());
}

void Game::RemoveDeadEnemies() {
  enemies_.erase(
      std::remove_if(enemies_.begin(), enemies_.end(),
                     [](const Enemy& enemy) { return enemy.IsDead(); }),
      enemies_.end());
}

void Game::SpawnEnemy() {
  vec2 spawn_point =
      tank_.GetPosition() + ci::randVec2() * static_cast<float>(window_width_);
  enemies_.emplace_back(spawn_point, kInitialEnemySpeed, &tank_);
}

void Game::DropBomb() { enemies_.clear(); }

bool Game::TankIsLoaded() {
  timer_.stop();
  bool is_loaded = false;
  if (timer_.getSeconds() > tank_.GetBulletConfig().delay) {
    is_loaded = true;
    timer_.start();
  } else {
    timer_.resume();
  }
  return is_loaded;
}

void Game::HandleTankEnemyCollision() {
  for (size_t i = 0; i < enemies_.size(); i++) {
    if (tank_.DidCollideWith(enemies_[i])) {
      tank_.DecrementLife();
      enemies_.erase(enemies_.begin() + i);
      return;
    }
  }
}

}  // namespace tank_hero