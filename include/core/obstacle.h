#ifndef TANK_HERO_OBSTACLE_H
#define TANK_HERO_OBSTACLE_H

#include "cinder/gl/gl.h"
#include "core/movable.h"
namespace tank_hero {
using glm::vec2;

class Obstacle {
 public:
  Obstacle(const vec2& top_left, const vec2& bottom_right);
  // Getters
  const vec2& GetTopLeft() const { return top_left_; }
  const vec2& GetBottomRight() const { return bottom_right_; }

  bool CheckCollisionWith(Movable object) const;
 private:
  vec2 top_left_;
  vec2 bottom_right_;
};

}  // namespace tank_hero

#endif  // TANK_HERO_OBSTACLE_H
