#ifndef TANK_HERO_OBSTACLE_H
#define TANK_HERO_OBSTACLE_H

#include <string>
#include <vector>

#include "bullet.h"
#include "cinder/gl/gl.h"
#include "movable.h"

namespace tank_hero {
using glm::vec2;
using std::string;
using std::vector;

class Obstacle {
 public:
  Obstacle(const vec2& top_left, const vec2& bottom_right);
  // Getters
  const vec2& GetTopLeft() const { return top_left_; }
  const vec2& GetBottomRight() const { return bottom_right_; }

  void HandleCollisionWith(Movable* movable) const;

 private:
  vector<string> FindCollisionDirection(const Movable& movable) const;

  vec2 top_left_;
  vec2 bottom_right_;
};

}  // namespace tank_hero

#endif  // TANK_HERO_OBSTACLE_H
