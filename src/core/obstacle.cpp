#include "core/obstacle.h"

namespace tank_hero {

Obstacle::Obstacle(const vec2& top_left, const vec2& bottom_right)
    : top_left_(top_left), bottom_right_(bottom_right) {}

bool Obstacle::CheckCollisionWith(Movable object) const {

  return false; }
}  // namespace tank_hero