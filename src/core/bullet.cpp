#include "core/bullet.h"
namespace tank_hero {
Bullet::Bullet(const Tank& tank, const vec2& mouse_pos)
    : position_(tank.GetPosition()),
      velocity_(glm::normalize(mouse_pos - position_) * kBulletSpeed),
      radius_(tank.GetBulletSize()) {}

void Bullet::Move() { position_ += velocity_; }

bool Bullet::DidHit(const Enemy& enemy) const {
  return glm::distance2(position_, enemy.GetPosition()) <=
         pow(radius_ + enemy.GetRadius(), 2);
}

bool Bullet::IsOutOfMap(size_t map_width) const {
  return (position_.x < 0 || position_.x > map_width || position_.y < 0 ||
          position_.y > map_width);
}

}  // namespace tank_hero