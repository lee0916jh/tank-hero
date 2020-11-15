#ifndef TANK_HERO_ENEMY_H
#define TANK_HERO_ENEMY_H

#include "cinder/gl/gl.h"
#include "core/tank.h"

constexpr float kEnemyRadius = 10;
namespace tank_hero {
using glm::vec2;

class Enemy {
 public:
  /// Constructor
  /// \param position Spawn position
  /// \param target Target to chase
  Enemy(const vec2& position, float speed, Tank* target);

  // Getters and Setters
  const vec2& GetPosition() const { return position_; }
  float GetRadius() const { return radius_; }
  bool IsDead() const { return dead_; }
  void Dies() { dead_ = true; }

  /// The Enemy moves towards the target
  void ApproachTank();

 private:
  vec2 position_;
  float radius_ = kEnemyRadius;
  float speed_;
  Tank* target_;
  bool dead_ = false;
};
}  // namespace tank_hero
#endif  // TANK_HERO_ENEMY_H
