#ifndef TANK_HERO_GAME_H
#define TANK_HERO_GAME_H
#include <algorithm>
#include <set>
#include <vector>

#include "bullet.h"
#include "cinder/Rand.h"
#include "cinder/Timer.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "enemy.h"
#include "obstacle.h"
#include "ranged_enemy.h"
#include "tank.h"

namespace tank_hero {
using ci::Timer;
using glm::vec2;
using std::set;
using std::vector;

constexpr size_t kFieldWidth = 2000;

constexpr size_t kRangedEnemySpawnDifficulty = 3;
constexpr float kMaxDifficulty = 20;
constexpr float kInitialEnemySpeed = 1;
constexpr float kInitialSpawnFreq = 2;

constexpr float kUpgradeAmount = 0.005;
constexpr float kEnemySpeedIncreaseAmount = 0.1;
constexpr float kEnemySpawnFreqReduceAmount = 0.1;

class Game {
 public:
  Game(size_t window_width,
       const vector<Obstacle>& obstacles = vector<Obstacle>());

  // Getters
  const Tank& GetTank() const { return tank_; }
  const vector<Enemy>& GetEnemies() const { return melee_enemies_; }
  const vector<RangedEnemy>& GetRangedEnemies() const {
    return ranged_enemies_;
  }
  const vector<Bullet>& GetTankBullets() const { return tank_bullets_; }
  const vector<Bullet>& GetEnemyBullets() const { return enemy_bullets_; }
  const vector<Obstacle>& GetObstacles() const { return obstacles_; }
  size_t GetCurrentLife() const { return tank_.GetLifeCount(); }
  float GetReloadTime() const { return tank_.GetReloadTime(); }
  size_t GetKillCount() const { return kill_count_; }
  size_t GetBombCount() const { return tank_.GetBombCount(); }
  bool IsOn() const { return tank_.IsAlive(); }

  void Update();

  /// Moves tank according to the given key input. If tank goes outside of the
  /// map, return it back onto the map.
  /// \param keys Pressed keys that determine where the tank moves.
  /// \param mouse_pos Mouse position which the tank gun will aim at.
  void HandleTankMovement(const set<int>& keys, const vec2& mouse_pos);

  /// Fires a bullet from the tank if tank is loaded.
  /// If tank isn't reloaded, bullet does not fire.
  void TryAndFireTankBullet();

  /// Drops bomb which kills enemies instantly only if tank has bombs left.
  void DropBomb();

  /// Spawns an enemy around the player.
  void SpawnEnemies();

  /// Increases speed and spawn frequency of newly spawned enemies.
  void IncreaseDifficulty();

 private:
  /// Fires a bullet from ranged enemies if they are loaded.
  /// If not reloaded, bullet does not fire.
  void TryAndFireEnemiesBullet();

  /// Checks if any of the tank's bullets hit an enemy. If a bullet hit an
  /// enemy, set the bullet inactive, and the enemy dead.
  void HandleTankBulletsHittingEnemies();

  /// Checks if any of the enemy's bullets hit the tank. If the tank is hit by a
  /// bullet, tank loses a life.
  void HandleEnemyBulletsHittingTank();

  /// Checks if any enemy in the vector hits the tank. If that happened, tank
  /// loses a life.
  template <typename EnemyType>
  void HandleTankEnemiesCollisions(vector<EnemyType>* enemies);

  /// Removes bullets that went outside the play area, or that are inactive.
  void RemoveInvalidBullets();

  /// Removes dead enemies that got hit by a bullet.
  void RemoveDeadEnemies();

  void HandleObjectsCollisionWithObstacles();

  void MoveGameObjects();

  size_t window_width_;
  size_t map_width_;

  // Game Objects
  Tank tank_;
  vector<Enemy> melee_enemies_;
  vector<RangedEnemy> ranged_enemies_;
  vector<Bullet> tank_bullets_;
  vector<Bullet> enemy_bullets_;
  vector<Obstacle> obstacles_;

  // Game Status
  Timer enemy_spawn_timer_;
  size_t kill_count_ = 0;
  size_t difficulty_ = 0;
  float new_enemy_speed_ = kInitialEnemySpeed;
  float enemy_spawn_delay_ = kInitialSpawnFreq;
};
}  // namespace tank_hero

#include "game.hpp"

#endif  // TANK_HERO_GAME_H
