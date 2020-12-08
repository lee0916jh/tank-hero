#ifndef TANK_HERO_ITEM_H
#define TANK_HERO_ITEM_H

#include <optional>

#include "cinder/gl/gl.h"
#include "ranged.h"
#include "tank.h"

namespace tank_hero {
using glm::vec2;

constexpr float kBigBulletSize = 20;
constexpr float kFastBulletSpeed = 20;

enum class ItemType { kLife, kShield, kBomb, kBigGun, kFastGun, kOriginalGun };

class Item {
 public:
  Item(const vec2& position, const ItemType& type,
       const std::optional<BulletConfig>& bullet_config = {});

  // Getters
  const vec2& GetPosition() const { return position_; }
  bool IsGun() const { return bullet_config_.has_value(); }
  const std::optional<BulletConfig>& GetBulletConfig() const;
  const ItemType& GetType() const { return type_; }

  bool IsInPickUpRange(const Tank& tank) const;

 private:
  vec2 position_;
  ItemType type_;
  std::optional<BulletConfig> bullet_config_;
};
}  // namespace tank_hero

#endif  // TANK_HERO_ITEM_H
