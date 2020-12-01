#include "core/game.h"

#include <set>

#include "catch2/catch.hpp"
#include "cinder/app/App.h"
using glm::vec2;
using tank_hero::Game;

TEST_CASE("Tank Movement tests", "[HandleTankMovement]") {
  Game game(100);  // Tank spawns at (50,50) with speed of 3

  std::set<int> keys;
  vec2 mouse_position(0, 0);
  SECTION("Tank moves left") {
    keys.insert(ci::app::KeyEvent::KEY_a);
    game.HandleTankMovement(keys, mouse_position);
    REQUIRE(game.GetTank().GetPosition() == vec2(47, 50));
  }
  SECTION("Tank moves right") {
    keys.insert(ci::app::KeyEvent::KEY_d);
    game.HandleTankMovement(keys, mouse_position);
    REQUIRE(game.GetTank().GetPosition() == vec2(53, 50));
  }
  SECTION("Tank moves up") {
    keys.insert(ci::app::KeyEvent::KEY_w);
    game.HandleTankMovement(keys, mouse_position);
    REQUIRE(game.GetTank().GetPosition() == vec2(50, 47));
  }
  SECTION("Tank moves down") {
    keys.insert(ci::app::KeyEvent::KEY_s);
    game.HandleTankMovement(keys, mouse_position);
    REQUIRE(game.GetTank().GetPosition() == vec2(50, 53));
  }
  SECTION("Tank moves in diagonal directions") {
    keys.insert(ci::app::KeyEvent::KEY_s);
    keys.insert(ci::app::KeyEvent::KEY_a);  // left down
    game.HandleTankMovement(keys, mouse_position);
    // moved 3 diagonally
    REQUIRE(game.GetTank().GetPosition().x == Approx(47.879));
    REQUIRE(game.GetTank().GetPosition().y == Approx(52.121));
  }
}

TEST_CASE(
    "HandleTankBulletsHittingEnemies erases killed enemies and increase kill "
    "count", "[HandleTankBulletsHittingEnemies]") {
  Game game(100);  // Tank spawns at (50,50) with speed of 3
  SECTION("Nothing happens when no one dies"){

  }
}