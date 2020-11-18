#ifndef TANK_HERO_ENEMY_H
#define TANK_HERO_ENEMY_H
#include "cinder/gl/gl.h"
#include "core/movable.h"
#include "core/tank.h"

namespace tank_hero {
using glm::vec2;

constexpr float kEnemyRadius = 10;

class Enemy : public Movable {
 public:
  /// Constructor
  /// \param position Spawn position
  /// \param target Target to chase
  Enemy(const vec2& position, float speed, Tank* target);

  // Getters and Setters
  float GetRadius() const { return radius_; }
  bool IsDead() const { return dead_; }
  void Dies() { dead_ = true; }

  /// The Enemy moves towards the target
  void Move() override;

 private:
  float radius_ = kEnemyRadius;
  Tank* target_;
  bool dead_ = false;
};
}  // namespace tank_hero
#endif  // TANK_HERO_ENEMY_H
