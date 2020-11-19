#include "core/game.h"

namespace tank_hero {

Game::Game(size_t window_width)
    : window_width_(window_width),
      tank_(vec2(window_width / 2, window_width / 2)),
      reload_timer_(0) {
  reload_timer_.start();
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
  bullets_.emplace_back(tank_, mouse_pos);
}

void Game::HandleBulletEnemyCollision() {
  for (Bullet& bullet : bullets_) {
    for (Enemy& enemy : enemies_) {
      if (bullet.DidHit(enemy)) {
        bullet.GoesInactive();
        enemy.Dies();
        kill_count_++;
        tank_.ReduceReloadTime(kUpgradeAmount);
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
  if (enemy_spawn_timer_.getSeconds() > enemy_spawn_freq_) {
    vec2 spawn_point = tank_.GetPosition() +
                       ci::randVec2() * static_cast<float>(window_width_);
    enemies_.emplace_back(spawn_point, new_enemy_speed_, &tank_);
    enemy_spawn_timer_.start();
  }
}

void Game::DropBomb() { enemies_.clear(); }

bool Game::TankIsLoaded() {
  if (reload_timer_.getSeconds() > tank_.GetReloadTime()) {
    reload_timer_.start();
    return true;
  }
  return false;
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

void Game::IncreaseDifficulty() {
  new_enemy_speed_ += kEnemySpeedIncreaseAmount;
  enemy_spawn_freq_ -= kEnemySpawnFreqReduceAmount;
}

}  // namespace tank_hero