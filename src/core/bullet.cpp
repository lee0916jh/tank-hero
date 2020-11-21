#include "core/bullet.h"
namespace tank_hero {
Bullet::Bullet(const vec2& from, const vec2& to,
               const BulletConfig& bullet_config)
    : Movable(from, glm::normalize(to - from), bullet_config.speed,
              bullet_config.radius) {}

bool Bullet::DidHit(const Enemy& enemy) const {
  return glm::distance2(position_, enemy.GetPosition()) <=
         pow(collider_radius_ + enemy.GetColliderRadius(), 2);
}

bool Bullet::IsOutOfMap(size_t map_width) const {
  return (position_.x < 0 || position_.x > map_width || position_.y < 0 ||
          position_.y > map_width);
}

}  // namespace tank_hero