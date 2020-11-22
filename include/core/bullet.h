#ifndef TANK_HERO_BULLET_H
#define TANK_HERO_BULLET_H

#include <vector>

#include "cinder/gl/gl.h"
#include "enemy.h"
#include "movable.h"
#include "tank.h"

namespace tank_hero {
using glm::vec2;
using std::vector;

class Bullet : public Movable {
 public:
  Bullet(const vec2& spawn_pos, const vec2& direction,
         const BulletConfig& bullet_config);

  // Getters and Setters
  bool IsActive() const { return active_; }
  void GoInactive() { active_ = false; }

  template <typename EnemyType>
  bool TryAndKillEnemy(vector<EnemyType>* enemies);
  /// Returns true only if the bullet is outside the map.
  bool IsOutOfMap(size_t map_width) const;

  /// Returns true only if the bullet collided with the tank.
  bool DidHit(const Tank& tank) const;

  /// Returns true only if the bullet collided with the enemy.
  bool DidHit(const Enemy& enemy) const;

 private:
  /// Returns true only if the bullet collided with the movable object.
  bool CheckCollision(const Movable& movable) const;

  bool active_ = true;
};
}  // namespace tank_hero

#include "bullet.hpp"

#endif  // TANK_HERO_BULLET_H
