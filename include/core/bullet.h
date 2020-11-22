#ifndef TANK_HERO_BULLET_H
#define TANK_HERO_BULLET_H

#include <vector>

#include "cinder/gl/gl.h"
#include "movable.h"
#include "ranged.h"

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

  /// Returns true only if the bullet is outside the map.
  bool IsOutOfMap(size_t map_width) const;

  /// Returns true only if the bullet collided with the movable object.
  bool DidHit(const Movable& movable) const;

  /// Kills an enemy in the vector if it's hit by this bullet.
  /// \tparam EnemyType The vector must contain an EnemyType.
  /// \param enemies Vector of Enemies to check.
  /// \return Returns the iterator to the killed enemy if it's killed or the
  /// iterator to the end if nobody is killed.
  template <typename EnemyType>
  typename vector<EnemyType>::iterator TryAndKillEnemy(
      vector<EnemyType>* enemies);

 private:
  bool active_ = true;
};
}  // namespace tank_hero

#include "bullet.hpp"

#endif  // TANK_HERO_BULLET_H
