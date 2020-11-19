#ifndef TANK_HERO_BULLET_H
#define TANK_HERO_BULLET_H

#include <vector>

#include "cinder/gl/gl.h"
#include "core/enemy.h"
#include "core/movable.h"
#include "core/tank.h"

namespace tank_hero {
using glm::vec2;

class Bullet : public Movable {
 public:
  Bullet(const Tank& tank, const vec2& mouse_pos);

  // Getters and Setters
  bool IsActive() const { return active_; }
  void GoesInactive() { active_ = false; }

  /// Returns true only if the bullet is outside the map.
  bool IsOutOfMap(size_t map_width) const;

  /// Returns true only if the bullet collided with the enemy.
  bool DidHit(const Enemy& enemy) const;

 private:
  bool active_ = true;
};
}  // namespace tank_hero
#endif  // TANK_HERO_BULLET_H
