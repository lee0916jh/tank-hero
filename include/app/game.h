#ifndef TANK_HERO_GAME_H
#define TANK_HERO_GAME_H
#include <algorithm>
#include <set>
#include <vector>

#include "cinder/Rand.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "components/bullet.h"
#include "components/enemy.h"
#include "components/tank.h"
#include "stdlib.h"

namespace tank_hero::app {
using ci::app::KeyEvent;
using glm::vec2;
using std::pair;
using std::set;
using std::vector;

constexpr size_t kFieldWidth = 1000;
constexpr float kInitialEnemySpeed = 1.0f;
const ci::Color kTankColor = ci::Color("green");
const ci::Color kEnemyColor = ci::Color("red");
const ci::Color kBulletColor = ci::Color("yellow");

class Game {
 public:
  Game(size_t window_width);

  /// Draws the tank, enemies, and bullets.
  void Draw() const;
  void Update();

  /// Moves tank according to the given key input
  /// \param keys Pressed keys that determine where the tank moves.
  void HandleTankMovement(const set<int>& keys);

  /// Fires a bullet from the tank to the mouse pointer.
  /// \param mouse_pos Position that bullet will fly to,
  void FireBullet(const vec2& mouse_pos);

  /// Kills enemies instantly.
  void DropBomb();

  /// Spawns an enemy around the player.
  void SpawnEnemy();

 private:
  void DrawTank() const;
  void DrawEnemies() const;
  void DrawBullets() const;

  /// Checks if any of the bullets hit an enemy, and if a bullet hit an enemy,
  /// set the bullet inactive, and the enemy dead.
  void HandleBulletEnemyCollision();

  /// Removes bullets that went outside the play area, or that are inactive.
  void RemoveInvalidBullets();

  /// Removes dead enemies that got hit by a bullet.
  void RemoveDeadEnemies();

  // member variables
  size_t window_width_;
  Tank tank_;
  vector<Enemy> enemies_;
  vector<Bullet> bullets_;
};
}  // namespace tank_hero::app
#endif  // TANK_HERO_GAME_H
