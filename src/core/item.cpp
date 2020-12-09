#include "core/item.h"
namespace tank_hero {
Item::Item(const vec2& position, const ItemType& type,
           const std::optional<BulletConfig>& bullet_config)
    : position_(position), type_(type), bullet_config_(bullet_config) {}

const std::optional<BulletConfig>& Item::GetBulletConfig() const {
  return bullet_config_;
}

bool Item::IsInPickUpRange(const Tank& tank) const {
  return glm::distance2(tank.GetPosition(), position_) <
         powf(tank.GetColliderRadius() + kItemRadius, 2);
}
}  // namespace tank_hero
