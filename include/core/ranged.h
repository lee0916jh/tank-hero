#ifndef TANK_HERO_RANGED_H
#define TANK_HERO_RANGED_H

#include "cinder/gl/gl.h"
namespace tank_hero {
using glm::vec2;

struct BulletConfig {
  float radius;
  float speed;
};

class Ranged {
 public:
  Ranged(float bullet_radius, float bullet_speed, float reload_time);

  // Getters and Setters
  float GetBulletRadius() const { return bullet_config_.radius; }
  float GetBulletSpeed() const { return bullet_config_.speed; }
  const BulletConfig& GetBulletConfig() const { return bullet_config_; }
  float GetReloadTime() const { return reload_time_; }
  const vec2& GetGunRotation() const { return gun_rotation_; }
  void ReduceReloadTime(float amount) { reload_time_ -= amount; }

 protected:
  BulletConfig bullet_config_;
  float reload_time_;
  vec2 gun_rotation_;
};
}  // namespace tank_hero
#endif  // TANK_HERO_RANGED_H
