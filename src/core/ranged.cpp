#include "core/ranged.h"

namespace tank_hero {

Ranged::Ranged(float bullet_radius, float bullet_speed, float reload_time)
    : bullet_config_({bullet_radius, bullet_speed}), reload_time_(reload_time) {
  reload_timer_.start();
}

void Ranged::ReduceReloadTime(float amount) {
  reload_time_ -= amount;
  if (reload_time_ < kMinReloadTime) reload_time_ = kMinReloadTime;
}
}  // namespace tank_hero