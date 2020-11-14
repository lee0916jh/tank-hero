#ifndef TANK_HERO_BULLET_H
#define TANK_HERO_BULLET_H

#include "cinder/gl/gl.h"
#include "core/tank.h"
namespace tank_hero {
using glm::vec2;

class Bullet {
 public:
  Bullet(Tank& tank, vec2 mouse_pos);

  const vec2& GetPosition() const { return position_; }
  float GetRadius() const { return radius_; }
  void Move();

 private:
  vec2 position_;
  vec2 velocity_;
  float radius_;
};
}  // namespace tank_hero
#endif  // TANK_HERO_BULLET_H
