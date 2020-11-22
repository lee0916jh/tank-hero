#ifndef TANK_HERO_OBSTACLE_H
#define TANK_HERO_OBSTACLE_H

#include <algorithm>
#include <string>
#include <unordered_map>
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

  template <typename MovableType>
  void HandleCollisionWith(vector<MovableType>* movables) const;

  void HandleCollisionWith(Tank* tank) const;

 private:
  void HandleCollisionWith(Movable* movable) const;
  string FindCollisionDirection(const Movable& movable) const;
  bool DidCollideWith(const Movable& movable) const;

  vec2 top_left_;
  vec2 bottom_right_;
};

}  // namespace tank_hero

#include "obstacle.hpp"

#endif  // TANK_HERO_OBSTACLE_H
