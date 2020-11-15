#ifndef TANK_HERO_ENEMY_H
#define TANK_HERO_ENEMY_H

#include "cinder/gl/gl.h"
#include "core/tank.h"

constexpr float kEnemyRadius = 10;
namespace tank_hero {
using glm::vec2;

class Enemy {
 public:
  Enemy(const vec2& position, float speed, Tank* target);

  // Getters
  const vec2& GetPosition() const { return position_; }
  float GetRadius() const { return radius_; }
  bool IsDead() const { return dead_; }

  void ApproachTank();
  void Dies() { dead_ = true; }

 private:
  vec2 position_;
  float radius_ = kEnemyRadius;
  float speed_;
  Tank* target_;

  bool dead_ = false;
};
}  // namespace tank_hero
#endif  // TANK_HERO_ENEMY_H
