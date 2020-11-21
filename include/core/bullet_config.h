#ifndef TANK_HERO_BULLET_CONFIG_H
#define TANK_HERO_BULLET_CONFIG_H

constexpr float kDefaultBulletSize = 5;
constexpr float kDefaultBulletSpeed = 8;
constexpr float kDefaultReloadTime = 1.5;

struct BulletConfig {
  float radius = kDefaultBulletSize;
  float speed = kDefaultBulletSpeed;
  float reload_time = kDefaultReloadTime;
};

#endif  // TANK_HERO_BULLET_CONFIG_H
