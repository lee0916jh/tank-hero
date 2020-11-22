#include "core/game.h"

namespace tank_hero {
using ci::app::KeyEvent;

Game::Game(size_t window_width, const vector<Obstacle>& obstacles)
    : window_width_(window_width),
      tank_(vec2(window_width / 2, window_width / 2)),
      obstacles_(obstacles) {
  enemy_spawn_timer_.start();
}

const vector<RangedEnemy>& Game::GetRangedEnemies() const {
  return ranged_enemies_;
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

  HandleTankBulletsHittingEnemies();
  HandleEnemyBulletsHittingTank();

  HandleTankEnemiesCollisions(&melee_enemies_);
  HandleTankEnemiesCollisions(&ranged_enemies_);

  HandleObjectsCollisionWithObstacles();
  RemoveInvalidBullets();
}

void Game::MoveGameObjects() {
  for (Bullet& tank_bullet : tank_bullets_) {
    tank_bullet.Move();
  }
  for (Bullet& enemy_bullet : enemy_bullets_) {
    enemy_bullet.Move();
  }
  for (Enemy& enemy : melee_enemies_) {
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

void Game::HandleTankBulletsHittingEnemies() {
  for (Bullet& tank_bullet : tank_bullets_) {
    auto killed_melee_enemy = tank_bullet.TryAndKillEnemy(&melee_enemies_);
    if (killed_melee_enemy != melee_enemies_.end()) {
      melee_enemies_.erase(killed_melee_enemy);
      kill_count_++;
      tank_.ReduceReloadTime(kUpgradeAmount);
      return;
    }

    auto killed_ranged_enemy = tank_bullet.TryAndKillEnemy(&ranged_enemies_);
    if (killed_ranged_enemy != ranged_enemies_.end()) {
      ranged_enemies_.erase(killed_ranged_enemy);
      kill_count_++;
      tank_.ReduceReloadTime(kUpgradeAmount);
    }
  }
}

void Game::HandleEnemyBulletsHittingTank() {
  for (Bullet& enemy_bullet : enemy_bullets_) {
    if (enemy_bullet.DidHit(tank_)) {
      enemy_bullet.GoInactive();
      tank_.DecrementLife();
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
  enemy_bullets_.erase(
      std::remove_if(enemy_bullets_.begin(), enemy_bullets_.end(),
                     [](const Bullet& bullet) {
                       return !bullet.IsActive() ||
                              bullet.IsOutOfMap(kFieldWidth);
                     }),
      enemy_bullets_.end());
}

void Game::SpawnEnemies() {
  if (enemy_spawn_timer_.getSeconds() > enemy_spawn_delay_) {
    vec2 spawn_point = tank_.GetPosition() +
                       ci::randVec2() * static_cast<float>(window_width_);
    melee_enemies_.emplace_back(spawn_point, new_enemy_speed_,
                                &tank_.GetPosition());

    if (difficulty_ > kRangedEnemySpawnDifficulty) {
      spawn_point = tank_.GetPosition() +
                    ci::randVec2() * static_cast<float>(window_width_);
      ranged_enemies_.emplace_back(spawn_point, new_enemy_speed_,
                                   &tank_.GetPosition());
    }
    enemy_spawn_timer_.start();
  }
}

void Game::DropBomb() {
  if (tank_.HasBomb()) {
    melee_enemies_.clear();
    ranged_enemies_.clear();
    tank_.DecrementBombCount();
  }
}

void Game::HandleObjectsCollisionWithObstacles() {
  for (const Obstacle& obstacle : obstacles_) {
    obstacle.HandleCollisionWith(&tank_bullets_);
    obstacle.HandleCollisionWith(&enemy_bullets_);
    obstacle.HandleCollisionWith(&melee_enemies_);
    obstacle.HandleCollisionWith(&ranged_enemies_);
    obstacle.HandleCollisionWith(&tank_);
  }
}

void Game::IncreaseDifficulty() {
  if (difficulty_ < kMaxDifficulty) {
    difficulty_++;
    new_enemy_speed_ += kEnemySpeedIncreaseAmount;
    enemy_spawn_delay_ -= kEnemySpawnFreqReduceAmount;
  }
}
}  // namespace tank_hero