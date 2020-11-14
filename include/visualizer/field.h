#ifndef TANK_HERO_FIELD_H
#define TANK_HERO_FIELD_H
#include <set>
#include <vector>

#include "cinder/Rand.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "core/bullet.h"
#include "core/enemy.h"
#include "core/tank.h"

namespace tank_hero::visualizer {
using ci::app::KeyEvent;
using std::vector;

constexpr float kFieldWidth = 10000;
const vec2 kSpawnPoint = vec2(100, 100);

class Field {
 public:
  Field();

  float GetWidth() { return width_; }
  void Draw() const;
  void Update();
  void HandleKeyInputs(const std::set<int>& keys);
  void FireBullet(const glm::ivec2& mouse_pos);

 private:
  void DrawTank() const;
  void DrawEnemies() const;
  void DrawBullets() const;

  // member variables
  float width_;
  Tank tank_;
  vector<Enemy> enemies_;
  vector<Bullet> bullets_;
};
}  // namespace tank_hero::visualizer
#endif  // TANK_HERO_FIELD_H
