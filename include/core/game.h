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
#include "tank.h"

namespace tank_hero {
using ci::Timer;
using ci::app::KeyEvent;
using glm::vec2;
using std::pair;
using std::set;
using std::vector;

constexpr size_t kFieldWidth = 2000;
constexpr float kInitialEnemySpeed = 1.0f;
const ci::Color kTankColor = ci::Color("green");
const ci::Color kEnemyColor = ci::Color("red");
const ci::Color kBulletColor = ci::Color("yellow");

class Game {
 public:
  Game(size_t window_width);

  // Getters
  const Tank& GetTank() const { return tank_; }
  const vector<Enemy>& GetEnemies() const { return enemies_; }
  const vector<Bullet>& GetBullets() const { return bullets_; }
  size_t GetCurrentLife() const { return tank_.GetLifeCount(); }
  float GetReloadTime() const { return tank_.GetBulletConfig().delay; }
  size_t GetKillCount() const { return kill_count_; }
  bool IsOn() const { return tank_.IsAlive(); }

  void Update();

  /// Moves tank according to the given key input. If tank goes outside of the
  /// map, return it back onto the map.
  /// \param keys Pressed keys that determine where the tank moves.
  void HandleTankMovement(const set<int>& keys);

  /// Fires a bullet from the tank to the mouse pointer if tank is loaded.
  /// If tank isn't reloaded, bullet does not fire.
  /// \param mouse_pos Position that bullet will fly to,
  void FireBullet(const vec2& mouse_pos);

  /// Kills enemies instantly.
  void DropBomb();

  /// Spawns an enemy around the player.
  void SpawnEnemy();

 private:
  /// Checks if any of the bullets hit an enemy, and if a bullet hit an enemy,
  /// set the bullet inactive, and the enemy dead.
  void HandleBulletEnemyCollision();

  /// Checks if an enemy hit the tank. If that happened, tank loses a life.
  void HandleTankEnemyCollision();

  /// Removes bullets that went outside the play area, or that are inactive.
  void RemoveInvalidBullets();

  /// Removes dead enemies that got hit by a bullet.
  void RemoveDeadEnemies();

  /// Returns true if tank is loaded and is ready to fire.
  bool TankIsLoaded();

  // member variables
  size_t window_width_;

 private:
  Tank tank_;
  vector<Enemy> enemies_;
  vector<Bullet> bullets_;
  Timer timer_;
  size_t kill_count_ = 0;
};
}  // namespace tank_hero
#endif  // TANK_HERO_GAME_H
