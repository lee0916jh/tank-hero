#include "core/bullet.h"
namespace tank_hero {
Bullet::Bullet(Tank& tank, vec2 mouse_pos)
    : position_(tank.GetPosition()),
      velocity_(glm::normalize(mouse_pos - position_)),
      radius_(tank.GetBulletSize()) {}

void Bullet::Move() { position_ += velocity_; }
}  // namespace tank_hero