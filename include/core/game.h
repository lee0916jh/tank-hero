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

const size_t kFieldWidth = 10000;
const vec2 kSpawnPoint = vec2(100, 100);
constexpr float kEnemySpeed = 1.0f;

class Game {
 public:
  Game();

  size_t GetWidth() { return width_; }
  void Draw() const;
  void Update();
  void HandleKeyInputs(const set<int>& keys);
  void FireBullet(const vec2& mouse_pos);

 private:
  void DrawTank() const;
  void DrawEnemies() const;
  void DrawBullets() const;
  void HandleBulletEnemyCollision();
  unsigned counter = 0;

  // member variables
  size_t width_;
  Tank tank_;
  vector<Enemy> enemies_;
  vector<Bullet> bullets_;
  void RemoveInvalidBullets();
  void RemoveDeadEnemies();
};
}  // namespace tank_hero::visualizer
#endif  // TANK_HERO_GAME_H
