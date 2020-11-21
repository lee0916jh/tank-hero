#include "core/ranged.h"

namespace tank_hero {

Ranged::Ranged(float bullet_radius, float bullet_speed, float reload_time)
    : bullet_config_({bullet_radius, bullet_speed}),
      reload_time_(reload_time) {}
}  // namespace tank_hero