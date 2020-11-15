#ifndef TANK_HERO_GAME_H
#define TANK_HERO_GAME_H
#include <algorithm>
#include <set>
#include <vector>

#include "cinder/Rand.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "core/bullet.h"
#include "core/enemy.h"
#include "core/tank.h"
#include "stdlib.h"

namespace tank_hero::visualizer {
using ci::app::KeyEvent;
using glm::vec2;
using std::pair;
using std::set;
using std::vector;

constexpr size_t kFieldWidth = 1000;
const vec2 kSpawnPoint = vec2(100, 100);
constexpr float kInitialEnemySpeed = 1.0f;

class Game {
 public:
  Game(size_t window_width);

  size_t GetWidth() { return map_width_; }
  void Draw() const;
  void Update();
  void HandleKeyInputs(const set<int>& keys);
  void FireBullet(const vec2& mouse_pos);
  void SpawnEnemy();

 private:
  void DrawTank() const;
  void DrawEnemies() const;
  void DrawBullets() const;
  void HandleBulletEnemyCollision();
  void RemoveInvalidBullets();
  void RemoveDeadEnemies();

  // member variables
  size_t map_width_;
  size_t window_width_;
  Tank tank_;
  vector<Enemy> enemies_;
  vector<Bullet> bullets_;
};
}  // namespace tank_hero::visualizer
#endif  // TANK_HERO_GAME_H
