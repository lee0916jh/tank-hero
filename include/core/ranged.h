#ifndef TANK_HERO_RANGED_H
#define TANK_HERO_RANGED_H

#include "cinder/Timer.h"
#include "cinder/gl/gl.h"

namespace tank_hero {
using ci::Timer;
using glm::vec2;

struct BulletConfig {
  float radius;
  float speed;
};

constexpr float kMinReloadTime = 0.3;

class Ranged {
 public:
  Ranged(float bullet_radius, float bullet_speed, float reload_time);

  // Getters and Setters
  const BulletConfig& GetBulletConfig() const { return bullet_config_; }
  float GetReloadTime() const { return reload_time_; }
  bool IsLoaded() const { return reload_timer_.getSeconds() >= reload_time_; }
  void SetBulletConfig(const BulletConfig& bullet_config);
  void ResetReloadTimer() { reload_timer_.start(); }

  /// Reduce the reload time by given amount only upto the minimum amount.
  /// (look kMinReloadTime for the minimum value)
  void ReduceReloadTime(float amount);

 protected:
  BulletConfig bullet_config_;
  float reload_time_;
  Timer reload_timer_;
};
}  // namespace tank_hero
#endif  // TANK_HERO_RANGED_H
