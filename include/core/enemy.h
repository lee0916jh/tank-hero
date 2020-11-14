#ifndef TANK_HERO_ENEMY_H
#define TANK_HERO_ENEMY_H

#include "cinder/gl/gl.h"
#include "core/tank.h"

namespace tank_hero {
using glm::vec2;

class Enemy {
 public:
  Enemy(const vec2& position, float speed, Tank* target);

  // Getters
  const vec2& GetPosition() const { return position_; };
  void ApproachTank() ;

 private:
  vec2 position_;
  float speed_;
  Tank* target_;
};
}  // namespace tank_hero
#endif  // TANK_HERO_ENEMY_H
