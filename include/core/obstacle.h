#ifndef TANK_HERO_OBSTACLE_H
#define TANK_HERO_OBSTACLE_H

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

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

  /// Pushes the Movable objects in the vector to closest non-obstacle terrain
  /// if the objects are colliding with this obstacle.
  /// \tparam MovableType Elements in the vector must be of a Movable type
  /// \param Vector of Movable objects
  template <typename MovableType>
  void HandleCollisionWith(vector<MovableType>* movables) const;

  /// Pushes the Movable object to closest non-obstacle terrain if the object
  /// is colliding with this obstacle.
  void HandleCollisionWith(Movable* movable) const;

 private:
  /// Checks if the movable object is colliding with this obstacle.
  /// \param movable  Movable object to check collision with
  /// \return Returns true only if the object is colliding with this obstacle.
  bool CheckCollision(const Movable& movable) const;

  /// Assuming collision happened, returns the direction where collision
  /// occurred.
  /// \param movable Movable object that collided with this obstacle
  /// \return "left", "right", "top", or "bottom", depending on the result
  string FindCollisionDirection(const Movable& movable) const;

  vec2 top_left_;
  vec2 bottom_right_;
};

}  // namespace tank_hero

#include "obstacle.hpp"

#endif  // TANK_HERO_OBSTACLE_H
