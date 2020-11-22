#include "core/game.h"

namespace tank_hero {
using ci::app::KeyEvent;

Game::Game(size_t window_width, const vector<Obstacle>& obstacles)
    : window_width_(window_width),
      tank_(vec2(window_width / 2, window_width / 2)),
      obstacles_(obstacles) {
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
  MoveGameObjects();
  TryAndFireEnemiesBullet();

  HandleBulletsEnemiesCollisions();
  HandleTanksEnemiesCollisions();
  HandleMovablesObstaclesCollisions();

  RemoveInvalidBullets();
  RemoveDeadEnemies();
}

void Game::MoveGameObjects() {
  for (Bullet& tank_bullet : tank_bullets_) {
    tank_bullet.Move();
  }
  for (Bullet& enemy_bullet : enemy_bullets_) {
    enemy_bullet.Move();
  }
  for (Enemy& enemy : enemies_) {
    enemy.Move();
  }
  for (RangedEnemy& ranged_enemy : ranged_enemies_) {
    ranged_enemy.Move();
  }
}

void Game::TryAndFireTankBullet() {
  if (tank_.IsLoaded()) {
    tank_bullets_.emplace_back(tank_.GetPosition(), tank_.GetGunRotation(),
                               tank_.GetBulletConfig());
    tank_.ResetReloadTimer();
  }
}

void Game::TryAndFireEnemiesBullet() {
  for (RangedEnemy& ranged_enemy : ranged_enemies_) {
    if (ranged_enemy.IsLoaded()) {
      enemy_bullets_.emplace_back(ranged_enemy.GetPosition(),
                                  ranged_enemy.GetDirection(),
                                  ranged_enemy.GetBulletConfig());
      ranged_enemy.ResetReloadTimer();
    }
  }
}

void Game::HandleBulletsEnemiesCollisions() {
  for (Bullet& bullet : tank_bullets_) {
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
  tank_bullets_.erase(std::remove_if(tank_bullets_.begin(), tank_bullets_.end(),
                                     [](const Bullet& bullet) {
                                       return !bullet.IsActive() ||
                                              bullet.IsOutOfMap(kFieldWidth);
                                     }),
                      tank_bullets_.end());
}

void Game::RemoveDeadEnemies() {
  enemies_.erase(
      std::remove_if(enemies_.begin(), enemies_.end(),
                     [](const Enemy& enemy) { return enemy.IsDead(); }),
      enemies_.end());
}

void Game::SpawnEnemies() {
  if (enemy_spawn_timer_.getSeconds() > enemy_spawn_freq_) {
    vec2 spawn_point = tank_.GetPosition() +
                       ci::randVec2() * static_cast<float>(window_width_);
    enemies_.emplace_back(spawn_point, new_enemy_speed_, &tank_.GetPosition());

    if (difficulty_ > 3) {
      spawn_point = tank_.GetPosition() +
                    ci::randVec2() * static_cast<float>(window_width_);
      ranged_enemies_.emplace_back(spawn_point, new_enemy_speed_,
                                   &tank_.GetPosition());
    }
    enemy_spawn_timer_.start();
  }
}

void Game::DropBomb() {
  enemies_.clear();
  //  ranged_enemies_.clear();
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
    for (Bullet& bullet : tank_bullets_) {
      obstacle.HandleCollisionWith(&bullet);
    }
    for (Enemy& enemy : enemies_) {
      obstacle.HandleCollisionWith(&enemy);
    }
    obstacle.HandleCollisionWith(&tank_);
  }
}

void Game::IncreaseDifficulty() {
  difficulty_++;
  new_enemy_speed_ += kEnemySpeedIncreaseAmount;
  enemy_spawn_freq_ -= kEnemySpawnFreqReduceAmount;
}

}  // namespace tank_hero