#ifndef TANK_HERO_ITEM_H
#define TANK_HERO_ITEM_H

#include <optional>

#include "cinder/gl/gl.h"
#include "math.h"
#include "ranged.h"
#include "tank.h"

namespace tank_hero {
using glm::vec2;

constexpr float kItemRadius = 10;
constexpr float kBigBulletSize = 20;
constexpr float kFastBulletSpeed = 20;
constexpr float kShotgunBulletSize = 10;
constexpr float kShotgunBulletSpeed = 5;
constexpr float kShotgunMaxRotation = M_PI / 6;
constexpr float kShotgunBulletCount = 5;

enum class ItemType {
  kLife,
  kShield,
  kBomb,
  kShotgun,
  kBigGun,
  kFastGun,
  kOriginalGun
};

class Tank;
class Item {
 public:
  Item(const vec2& position, const ItemType& type,
       const std::optional<BulletConfig>& bullet_config = {});

  // Getters
  const vec2& GetPosition() const { return position_; }
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
