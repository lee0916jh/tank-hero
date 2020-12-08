#ifndef TANK_HERO_BULLET_H
#define TANK_HERO_BULLET_H

#include <vector>

#include "cinder/gl/gl.h"
#include "movable.h"
#include "ranged.h"
#include "tank.h"

namespace tank_hero {
using glm::vec2;
using std::vector;

constexpr float kDefaultBulletSize = 5;
constexpr float kDefaultBulletSpeed = 8;
constexpr float kDefaultReloadTime = 1.5;

class Bullet : public Movable {
 public:
  Bullet(const vec2& spawn_pos, const vec2& direction,
         const BulletConfig& bullet_config);

  // Getters and Setters
  bool IsBig() const { return collider_radius_ > kDefaultBulletSize; }
  bool IsActive() const { return active_; }
  void GoInactive() { active_ = false; }

  /// Returns true only if the bullet is outside the map.
  bool IsOutOfMap(size_t map_width) const;

  /// Returns true only if the bullet collided with the movable object.
  bool DidHit(const Movable& movable) const;

  /// Returns the iterator pointing to the killed enemy (enemy that collided
  /// with this bullet). If no one is killed, returns the iterator to the end.
  /// \tparam EnemyType The vector must contain an EnemyType.
  /// \param enemies Vector of Enemies to check.
  /// \return Returns the iterator to the killed enemy if it's killed or the
  /// iterator to the end if nobody is killed.
  template <typename EnemyType>
  typename vector<EnemyType>::iterator GetKilledEnemy(
      vector<EnemyType>* enemies);

 private:
  bool active_ = true;
};
}  // namespace tank_hero

#include "bullet.hpp"

#endif  // TANK_HERO_BULLET_H
