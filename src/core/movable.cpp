#include "core/movable.h"
namespace tank_hero {
Movable::Movable(const glm::vec2& position, const glm::vec2& direction,
                 float speed, size_t size)
    : position_(position), direction_(direction), speed_(speed), size_(size) {}

void Movable::Move() { position_ += direction_ * speed_; }
}  // namespace tank_hero
