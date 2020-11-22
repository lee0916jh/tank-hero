#ifndef TANK_HERO_ENEMY_H
#define TANK_HERO_ENEMY_H

#include "cinder/gl/gl.h"
#include "movable.h"

namespace tank_hero {
using glm::vec2;

constexpr float kEnemyRadius = 10;

class Enemy : public Movable {
 public:
  /// Constructor
  /// \param position Spawn position
  /// \param tank Target to chase
  Enemy(const vec2& position, float speed, const vec2* target);

  Enemy(const Enemy& source) = default;
  Enemy(Enemy&& source) = default;
  Enemy& operator=(const Enemy& source) = default;
  Enemy& operator=(Enemy&& source) = default;
  ~Enemy() = default;

  /// The Enemy moves towards the target
  virtual void Move() override;

 protected:
  const vec2* target_;
};
}  // namespace tank_hero
#endif  // TANK_HERO_ENEMY_H
