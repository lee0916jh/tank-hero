#include "core/game.h"

#include <set>

#include "catch2/catch.hpp"
#include "cinder/app/App.h"
using glm::vec2;
using tank_hero::Game;

TEST_CASE("Tank Movement tests", "[HandleTankMovement]") {
  Game game(100);  // Tank spawns at (50,50) with speed of 2

  std::set<int> keys;
  SECTION("Tank moves left") {
    keys.insert(ci::app::KeyEvent::KEY_a);
    game.HandleTankMovement(keys);
    REQUIRE(game.GetTank().GetPosition() == vec2(48, 50));
  }
  SECTION("Tank moves right") {
    keys.insert(ci::app::KeyEvent::KEY_d);
    game.HandleTankMovement(keys);
    REQUIRE(game.GetTank().GetPosition() == vec2(52, 50));
  }
  SECTION("Tank moves up") {
    keys.insert(ci::app::KeyEvent::KEY_w);
    game.HandleTankMovement(keys);
    REQUIRE(game.GetTank().GetPosition() == vec2(50, 48));
  }
  SECTION("Tank moves down") {
    keys.insert(ci::app::KeyEvent::KEY_s);
    game.HandleTankMovement(keys);
    REQUIRE(game.GetTank().GetPosition() == vec2(50, 52));
  }
  SECTION("Tank moves in diagonal directions") {
    keys.insert(ci::app::KeyEvent::KEY_s);
    keys.insert(ci::app::KeyEvent::KEY_a);  // left down
    game.HandleTankMovement(keys);
    REQUIRE(game.GetTank().GetPosition() == vec2(48, 52));
  }
}

TEST_CASE("TankTryAndFireBullet shoots a bullet from a tank", "[TankTryAndFireBullet]") {
  Game game(100);  // Tank spawns at (50,50) with speed of 2

  SECTION("Shoots bullet to the right") {
    game.TankTryAndFireBullet(vec2(100, 50));
    REQUIRE(game.GetBullets()[0].GetPosition() == vec2(50, 50));
    game.Update();
    REQUIRE(game.GetBullets()[0].GetPosition() == vec2(58, 50));
  }
  SECTION("Shoots bullet to the left") {
    game.TankTryAndFireBullet(vec2(0, 50));
    REQUIRE(game.GetBullets()[0].GetPosition() == vec2(50, 50));
    game.Update();
    REQUIRE(game.GetBullets()[0].GetPosition() == vec2(42, 50));
  }
  SECTION("Shoots bullet to the top") {
    game.TankTryAndFireBullet(vec2(50, 0));
    REQUIRE(game.GetBullets()[0].GetPosition() == vec2(50, 50));
    game.Update();
    REQUIRE(game.GetBullets()[0].GetPosition() == vec2(50, 42));
  }
  SECTION("Shoots bullet to the bottom") {
    game.TankTryAndFireBullet(vec2(50, 100));
    REQUIRE(game.GetBullets()[0].GetPosition() == vec2(50, 50));
    game.Update();
    REQUIRE(game.GetBullets()[0].GetPosition() == vec2(50, 58));
  }
  SECTION("Shoots bullet diagonally") {
    game.TankTryAndFireBullet(vec2(51, 51));
    REQUIRE(game.GetBullets()[0].GetPosition() == vec2(50, 50));
    game.Update();
    const vec2& bullet_pos = game.GetBullets()[0].GetPosition();
    REQUIRE(bullet_pos.x == Approx(55.657).margin(.0001));
    REQUIRE(bullet_pos.y == Approx(55.657).margin(.0001));
  }
}

TEST_CASE("Enemy spawns <window size> away from the player)", "[SpawnEnemy]") {
  Game game(100);
  for (size_t i = 0; i < 5; i++) {
    game.SpawnEnemy();
    REQUIRE(glm::distance(game.GetEnemies()[i].GetPosition(),
                          game.GetTank().GetPosition()) == Approx(100));
  }
}

TEST_CASE("DropBomb instantly kills all enemies", "[DropBomb]") {
  Game game(100);
  for (size_t i = 0; i < 100; i++) {
    game.SpawnEnemy();
  }
  REQUIRE(game.GetEnemies().size() == 100);
  game.DropBomb();
  REQUIRE(game.GetEnemies().size() == 0);
}
