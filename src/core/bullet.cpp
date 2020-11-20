#include "core/bullet.h"
namespace tank_hero {
Bullet::Bullet(const Tank& tank, const vec2& mouse_pos)
    : Movable(tank.GetPosition(),
              glm::normalize(mouse_pos - tank.GetPosition()),
              tank.GetBulletSpeed(), tank.GetBulletSize()) {}
bool Bullet::DidHit(const Enemy& enemy) const {
  return glm::distance2(position_, enemy.GetPosition()) <=
         pow(collider_radius_ + enemy.GetColliderRadius(), 2);
}

bool Bullet::IsOutOfMap(size_t map_width) const {
  return (position_.x < 0 || position_.x > map_width || position_.y < 0 ||
          position_.y > map_width);
}

}  // namespace tank_hero