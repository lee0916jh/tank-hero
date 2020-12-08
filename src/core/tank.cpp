#include "core/tank.h"

namespace tank_hero {
Tank::Tank(const vec2& position)
    : Movable(position, position, kDefaultSpeed, kTankSize / 2),
      Ranged(kDefaultBulletSize, kDefaultBulletSpeed, kDefaultReloadTime),
      is_shielded_(false),
      has_shotgun_(false) {}

void Tank::MoveUp() {
  direction_ = vec2(0, -1);
  Move();
}

void Tank::MoveDown() {
  direction_ = vec2(0, 1);
  Move();
}

void Tank::MoveLeft() {
  direction_ = vec2(-1, 0);
  Move();
}

void Tank::MoveRight() {
  direction_ = vec2(1, 0);
  Move();
}

void Tank::MoveUpLeft() {
  direction_ = glm::normalize(vec2(-1, -1));
  Move();
}

void Tank::MoveUpRight() {
  direction_ = glm::normalize(vec2(1, -1));
  Move();
}

void Tank::MoveDownLeft() {
  direction_ = glm::normalize(vec2(-1, 1));
  Move();
}

void Tank::MoveDownRight() {
  direction_ = glm::normalize(vec2(1, 1));
  Move();
}

void Tank::RotateGun(const vec2& direction) {
  gun_rotation_ = glm::normalize(direction - position_);
}

void Tank::KeepInMap(const size_t field_width) {
  if (position_.x < collider_radius_) position_.x = collider_radius_;
  if (position_.y < collider_radius_) position_.y = collider_radius_;
  if (position_.x > field_width - collider_radius_) {
    position_.x = field_width - collider_radius_;
  }
  if (position_.y > field_width - collider_radius_) {
    position_.y = field_width - collider_radius_;
  }
}

Bullet Tank::FireBullet(float rotation) {
  vec2 bullet_direction = glm::rotate(gun_rotation_, rotation);
  ResetReloadTimer();
  return Bullet(position_ + kTankSize / 2 * gun_rotation_, bullet_direction,
                bullet_config_);
}

void Tank::ApplyItem(const Item& item) {
  switch (item.GetType()) {
    case ItemType::kLife:
      life_++;
      break;
    case ItemType::kShield:
      is_shielded_ = true;
      break;
    case ItemType::kBomb:
      bomb_++;
      break;
    case ItemType::kShotgun:
      has_shotgun_ = true;
      bullet_config_ = item.GetBulletConfig().value();
      break;
    default:  // when the item is a gun but not a shotgun
      has_shotgun_ = false;
      bullet_config_ = item.GetBulletConfig().value();
      break;
  }
}

void Tank::LoseLifeOrShield() {
  if (this->is_shielded_) {
    is_shielded_ = false;
  } else {
    life_--;
  }
}
}  // namespace tank_hero
