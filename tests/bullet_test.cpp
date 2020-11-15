#include "core/bullet.h"

#include <catch2/catch.hpp>

#include "cinder/gl/gl.h"
#include "core/tank.h"

using glm::vec2;
using tank_hero::Bullet;
using tank_hero::Enemy;
using tank_hero::Tank;

TEST_CASE("Bullet Moves", "[Move]") {
  Tank tank(vec2(100, 100));
  SECTION("Bullet Moves Right") {
    Bullet bullet(tank, vec2(200, 100));
    bullet.Move();
    REQUIRE(bullet.GetPosition() == vec2(107, 100));  // default speed is 7
  }
  SECTION("Bullet Moves Left") {
    Bullet bullet(tank, vec2(0, 100));
    bullet.Move();
    REQUIRE(bullet.GetPosition() == vec2(93, 100));
  }
  SECTION("Bullet Moves Up") {
    Bullet bullet(tank, vec2(100, 0));
    bullet.Move();
    REQUIRE(bullet.GetPosition() == vec2(100, 93));
  }
  SECTION("Bullet Moves Down") {
    Bullet bullet(tank, vec2(100, 200));
    bullet.Move();
    REQUIRE(bullet.GetPosition() == vec2(100, 107));
  }
}

TEST_CASE("IsOutOfMap returns true when the bullet goes outside the map.",
          "[IsOutOfMap]") {
  Tank tank(vec2(5, 5));
  SECTION("Bullet crosses boundary to the top") {
    Bullet bullet(tank, vec2(5, 0));       // speed = 7
    REQUIRE_FALSE(bullet.IsOutOfMap(10));  // 10 x 10 map
    bullet.Move();
    REQUIRE(bullet.IsOutOfMap(10));
  }
  SECTION("Bullet crosses boundary to the right") {
    Bullet bullet(tank, vec2(10, 5));
    REQUIRE_FALSE(bullet.IsOutOfMap(10));
    bullet.Move();
    REQUIRE(bullet.IsOutOfMap(10));
  }
  SECTION("Bullet crosses boundary to the bottom") {
    Bullet bullet(tank, vec2(5, 10));
    REQUIRE_FALSE(bullet.IsOutOfMap(10));
    bullet.Move();
    REQUIRE(bullet.IsOutOfMap(10));
  }
  SECTION("Bullet crosses boundary to the left") {
    Bullet bullet(tank, vec2(0, 5));
    REQUIRE_FALSE(bullet.IsOutOfMap(10));
    bullet.Move();
    REQUIRE(bullet.IsOutOfMap(10));
  }
}

TEST_CASE("DidHit returns true only if it hits the enemy", "[DidHit]") {
  Tank tank(vec2(50, 50));
  Bullet bullet(tank, vec2(50, 100));   // radius 5
  Enemy enemy(vec2(50, 70), 0, &tank);  // radius 10
  REQUIRE_FALSE(bullet.DidHit(enemy));
  bullet.Move();
  REQUIRE(bullet.DidHit(enemy));
}