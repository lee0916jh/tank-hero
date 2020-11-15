#ifndef TANK_HERO_BULLET_H
#define TANK_HERO_BULLET_H

#include <vector>

#include "cinder/gl/gl.h"
#include "core/enemy.h"
#include "core/tank.h"

namespace tank_hero {
using glm::vec2;

const float kBulletSpeed = 7.0f;

class Bullet {
 public:
  Bullet(const Tank& tank, const vec2& mouse_pos);

  // Getters and Setters
  const vec2& GetPosition() const { return position_; }
  float GetRadius() const { return radius_; }
  bool IsActive() const { return active_; }
  void GoesInactive() { active_ = false; }

  /// Returns true only if the bullet is outside the map.
  bool IsOutOfMap(size_t map_width) const;

  /// Moves the bullet by 1 unit of time.
  void Move();

  /// Returns true if the bullet collided with the enemy.
  bool DidHit(const Enemy& enemy) const;

 private:
  vec2 position_;
  vec2 velocity_;
  float radius_;
  bool active_ = true;
};
}  // namespace tank_hero
#endif  // TANK_HERO_BULLET_H
