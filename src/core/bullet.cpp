#include "core/bullet.h"
namespace tank_hero {
Bullet::Bullet(const vec2& spawn_pos, const vec2& direction,
               const BulletConfig& bullet_config)
    : Movable(spawn_pos, glm::normalize(direction), bullet_config.speed,
              bullet_config.radius) {}

bool Bullet::DidHit(const Movable& movable) const {
  return glm::distance2(position_, movable.GetPosition()) <=
         pow(collider_radius_ + movable.GetColliderRadius(), 2);
}

bool Bullet::IsOutOfMap(size_t map_width) const {
  return (position_.x < 0 || position_.x > map_width || position_.y < 0 ||
          position_.y > map_width);
}
}  // namespace tank_hero