#include "core/game.h"

namespace tank_hero {
using ci::app::KeyEvent;

Game::Game(size_t window_width, const vector<Obstacle>& obstacles)
    : window_width_(window_width),
      tank_(vec2(window_width / 2, window_width / 2)),
      obstacles_(obstacles) {
  enemy_spawn_timer_.start();
  item_spawn_timer_.start();
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
  HandleItemPickUp();
}

void Game::HandleItemPickUp() {
  for (auto item_it = items_.begin(); item_it != items_.end(); item_it++) {
    if (item_it->IsInPickUpRange(tank_)) {
      switch (item_it->GetType()) {
        case ItemType::kLife:
          tank_.IncrementLife();
          break;
        case ItemType::kShield:
          tank_.SetShielded(true);
          break;
        case ItemType::kBomb:
          tank_.IncrementBombCount();
          break;
        default:  // when Item is a gun
          tank_.SetBulletConfig(item_it->GetBulletConfig().value());
          break;
      }
      items_.erase(item_it);
      return;
    }
  }
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
    // handles bullet's killing of melee enemies
    auto killed_melee = tank_bullet.GetKilledEnemy(&melee_enemies_);
    if (killed_melee != melee_enemies_.end()) {
      melee_enemies_.erase(killed_melee);
      kill_count_++;
      tank_.ReduceReloadTime(kUpgradeAmount);
      return;
    }
    // handles bullet's killing of ranged enemies
    auto killed_ranged = tank_bullet.GetKilledEnemy(&ranged_enemies_);
    if (killed_ranged != ranged_enemies_.end()) {
      ranged_enemies_.erase(killed_ranged);
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
  if (enemy_spawn_timer_.getSeconds() > enemy_spawn_cooldown_) {
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

void Game::SpawnItem() {
  if (item_spawn_timer_.getSeconds() > item_spawn_cooldown_) {
    vec2 random_pos(rand() % kFieldWidth, rand() % kFieldWidth);
    int random_item_code = rand() % kNumItems;
    BulletConfig bullet_config{kDefaultBulletSize, kDefaultBulletSpeed};

    switch (random_item_code) {
      case 0:
        items_.emplace_back(random_pos, ItemType::kLife);
        break;
      case 1:
        items_.emplace_back(random_pos, ItemType::kShield);
        break;
      case 2:
        items_.emplace_back(random_pos, ItemType::kBomb);
        break;
      case 3:
        bullet_config.radius = kBigBulletSize;
        items_.emplace_back(random_pos, ItemType::kBigGun, bullet_config);
        break;
      case 4:
        bullet_config.speed = kFastBulletSpeed;
        items_.emplace_back(random_pos, ItemType::kFastGun, bullet_config);
        break;
      case 5:
        items_.emplace_back(random_pos, ItemType::kOriginalGun, bullet_config);
        break;
      default:
        break;
    }
    item_spawn_timer_.start();
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
    enemy_spawn_cooldown_ -= kEnemySpawnFreqReduceAmount;
  }
}

}  // namespace tank_hero