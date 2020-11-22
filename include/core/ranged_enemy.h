#ifndef TANK_HERO_RANGED_ENEMY_H
#define TANK_HERO_RANGED_ENEMY_H

#include "cinder/gl/gl.h"
#include "enemy.h"
#include "ranged.h"

const float kEnemyBulletSize = 5;
const float kEnemyBulletSpeed = 5;
const float kEnemyReloadTime = 4;

const float kRangedEnemyMinDistance = 300;

namespace tank_hero {
using glm::vec2;

class RangedEnemy : public Enemy, public Ranged {
 public:
  RangedEnemy(const vec2& position, float speed, const vec2* target);

  void Move() override;
};

}  // namespace tank_hero

#endif  // TANK_HERO_RANGED_ENEMY_H
