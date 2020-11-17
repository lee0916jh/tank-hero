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

  void Draw() const;
  void Update();
  /// Move tank according to the given key input
  /// \param keys Pressed keys that determine where the tank moves.
  void HandleTankMovement(const set<int>& keys);
  void FireBullet(const vec2& mouse_pos);
  void DropBomb();
  void SpawnEnemy();

 private:
  void DrawTank() const;
  void DrawEnemies() const;
  void DrawBullets() const;
  void HandleBulletEnemyCollision();
  void RemoveInvalidBullets();
  void RemoveDeadEnemies();

  // member variables
  size_t window_width_;
  Tank tank_;
  vector<Enemy> enemies_;
  vector<Bullet> bullets_;
};
}  // namespace tank_hero::app
#endif  // TANK_HERO_GAME_H
