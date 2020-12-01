#include "core/obstacle.h"

#include "catch2/catch.hpp"
#include "cinder/gl/gl.h"
#include "core/bullet.h"
#include "core/tank.h"

using glm::vec2;
using tank_hero::Bullet;
using tank_hero::BulletConfig;
using tank_hero::Obstacle;
using tank_hero::Tank;

TEST_CASE("When a bullet and an obstacle collide, bullet dies") {
  Obstacle obstacle(vec2(10, 10), vec2(30, 30));
  vec2 spawn_pos(5, 20);
  BulletConfig config{1, 1};
  SECTION("Left collision") {
    Bullet bullet(spawn_pos, vec2(20, 20), config);
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE(bullet.IsActive());  // did not collide yet
    bullet.Move();
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE_FALSE(bullet.IsActive());
  }
  SECTION("Right collision") {
    Tank tank(vec2(35, 20));
    Bullet bullet(spawn_pos, vec2(20, 20), config);
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE(bullet.IsActive());  // did not collide yet
    bullet.Move();
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE_FALSE(bullet.IsActive());
  }
  SECTION("Top collision") {
    Tank tank(vec2(20, 5));
    Bullet bullet(spawn_pos, vec2(20, 20), config);
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE(bullet.IsActive());  // did not collide yet
    bullet.Move();
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE_FALSE(bullet.IsActive());
  }
  SECTION("Left collision") {
    Tank tank(vec2(20, 35));
    Bullet bullet(spawn_pos, vec2(20, 20), config);
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE(bullet.IsActive());  // did not collide yet
    bullet.Move();
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE_FALSE(bullet.IsActive());
  }
}