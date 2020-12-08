#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "bullet.h"
#include "cinder/gl/gl.h"
#include "enemy.h"
#include "item.h"
#include "movable.h"
#include "ranged.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultSpeed = 3;
constexpr float kTankSize = 60;

constexpr int kInitialLifeCount = 5;
constexpr int kInitialBombCount = 5;

class Enemy;
class Bullet;
class Item;
class Tank : public Movable, public Ranged {
 public:
  explicit Tank(const vec2& position);

  // Getters and Setters
  const vec2& GetGunRotation() const { return gun_rotation_; }
  bool IsAlive() const { return life_ > 0; }
  bool HasBomb() const { return bomb_ > 0; }
  bool HasShotgun() const { return has_shotgun_; }
  int GetLifeCount() const { return life_; };
  int GetBombCount() const { return bomb_; };
  bool IsShielded() const { return is_shielded_; }
  void DecrementBombCount() { bomb_--; }

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  void MoveUpLeft();
  void MoveUpRight();
  void MoveDownLeft();
  void MoveDownRight();

  /// Puts the tank back into the map if it went outside the map.
  /// \param field_width Size of the map
  void KeepInMap(const size_t field_width);

  /// Rotates the gun towards the direction
  void RotateGun(const vec2& direction);

  /// Returns a bullet fired from the tank, with the tank's current bullet
  /// configuration. Optionally, rotation in degree can be passed in
  /// (default rotation = 0).
  Bullet FireBullet(float rotation = 0);

  /// Apply item's effect to the tank according to the item type.
  void ApplyItem(const Item& item);

  /// Removes shield if the tank is currently shielded. Otherwise, decrement
  /// the tank's life by 1.
  void LoseLifeOrShield();

 private:
  int life_ = kInitialLifeCount;
  int bomb_ = kInitialBombCount;
  vec2 gun_rotation_;
  bool is_shielded_;
  bool has_shotgun_;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
