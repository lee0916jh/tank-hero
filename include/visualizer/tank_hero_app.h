#ifndef TANK_HERO_TANK_HERO_APP_H
#define TANK_HERO_TANK_HERO_APP_H

#include <set>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace tank_hero::visualizer {
using ci::app::KeyEvent;
using glm::vec2;

constexpr int kWindowSize = 1000;
const vec2 kSpawnPoint = vec2(100, 100);

class TankHeroApp : public ci::app::App {
 public:
  TankHeroApp();

  void draw() override;
  void update() override;
  void keyDown(KeyEvent event) override;
  void keyUp(KeyEvent event) override;

 private:
  void HandleKeyInputs();

  // data members
  std::set<int> held_keys_;
  Tank tank_;
};

}  // namespace tank_hero::visualizer
#endif  // TANK_HERO_TANK_HERO_APP_H
