#include "core/tank.h"
namespace tank_hero {
Tank::Tank(const vec2& position) : position_(position), speed_(kDefaultSpeed) {}

void Tank::MoveUp() { position_ += speed_ * vec2(0, -1); }

void Tank::MoveDown() { position_ += speed_ * vec2(0, 1); }

void Tank::MoveLeft() { position_ += speed_ * vec2(-1, 0); }

void Tank::MoveRight() { position_ += speed_ * vec2(1, 0); }

}  // namespace tank_hero
