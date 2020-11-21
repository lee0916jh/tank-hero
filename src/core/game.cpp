#include "core/game.h"

namespace tank_hero {
using ci::app::KeyEvent;

Game::Game(size_t window_width, const vector<Obstacle>& obstacles)
    : window_width_(window_width),
      tank_(vec2(window_width / 2, window_width / 2)),
      obstacles_(obstacles) {
  reload_timer_.start();
  enemy_spawn_timer_.start();
}

void Game::HandleTankMovement(const set<int>& keys, const vec2& mouse_pos) {
  if (keys.contains(KeyEvent::KEY_w) && keys.contains(KeyEvent::KEY_a)) {
    tank_.MoveUpLeft();
  } else if (keys.contains(KeyEvent::KEY_w) && keys.contains(KeyEvent::KEY_d)) {
    tank_.MoveUpRight();
  } else if (keys.contains(KeyEvent::KEY_s) && keys.contains(KeyEvent::KEY_a)) {
    tank_.MoveDownLeft();
  } else if (keys.contains(KeyEvent::KEY_s) && keys.contains(KeyEvent::KEY_d)) {
    tank_.MoveDownRight();
  } else if (keys.contains(KeyEvent::KEY_w)) {
    tank_.MoveUp();
  } else if (keys.contains(KeyEvent::KEY_s)) {
    tank_.MoveDown();
  } else if (keys.contains(KeyEvent::KEY_a)) {
    tank_.MoveLeft();
  } else if (keys.contains(KeyEvent::KEY_d)) {
    tank_.MoveRight();
  }

  tank_.KeepInMap(map_width_);
  tank_.RotateGun(mouse_pos);
}

void Game::Update() {
  for (Bullet& bullet : bullets_) {
    bullet.Move();
  }
  for (Enemy& enemy : enemies_) {
    enemy.Move();
  }

  HandleBulletsEnemiesCollisions();
  HandleTanksEnemiesCollisions();
  HandleMovablesObstaclesCollisions();

  RemoveInvalidBullets();
  RemoveDeadEnemies();
}

void Game::FireBullet(const vec2& mouse_pos) {
  bullets_.emplace_back(tank_.GetPosition(), mouse_pos,
                        tank_.GetBulletConfig());
}

void Game::HandleBulletsEnemiesCollisions() {
  for (Bullet& bullet : bullets_) {
    for (Enemy& enemy : enemies_) {
      if (bullet.DidHit(enemy)) {
        bullet.MakeInactive();
        enemy.Die();
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
    enemies_.emplace_back(spawn_point, new_enemy_speed_, &tank_.GetPosition());
    enemy_spawn_timer_.start();
  }
}

void Game::DropBomb() { enemies_.clear(); }

bool Game::TankIsLoaded() {
  if (reload_timer_.getSeconds() > tank_.GetBulletConfig().reload_time) {
    reload_timer_.start();
    return true;
  }
  return false;
}

void Game::HandleTanksEnemiesCollisions() {
  for (size_t i = 0; i < enemies_.size(); i++) {
    if (tank_.DidCollideWith(enemies_[i])) {
      tank_.DecrementLife();
      enemies_.erase(enemies_.begin() + i);
      return;
    }
  }
}

void Game::HandleMovablesObstaclesCollisions() {
  for (const Obstacle& obstacle : obstacles_) {
    for (Bullet& bullet : bullets_) {
      obstacle.HandleCollisionWith(&bullet);
    }
    for (Enemy& enemy : enemies_) {
      obstacle.HandleCollisionWith(&enemy);
    }
    obstacle.HandleCollisionWith(&tank_);
  }
}

void Game::IncreaseDifficulty() {
  new_enemy_speed_ += kEnemySpeedIncreaseAmount;
  enemy_spawn_freq_ -= kEnemySpawnFreqReduceAmount;
}

}  // namespace tank_hero