#include "core/movable.h"
namespace tank_hero {
Movable::Movable(const glm::vec2& position, const glm::vec2& direction,
                 float speed, size_t collider_radius)
    : position_(position),
      direction_(direction),
      speed_(speed),
      collider_radius_(collider_radius) {}

void Movable::Move() { position_ += direction_ * speed_; }

bool Movable::DidCollideWith(const Movable& other) const {
  return glm::distance2(position_, other.GetPosition()) <
         pow(collider_radius_ + other.GetColliderRadius(), 2);
}
}  // namespace tank_hero
