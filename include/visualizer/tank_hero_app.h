#ifndef TANK_HERO_TANK_HERO_APP_H
#define TANK_HERO_TANK_HERO_APP_H

#include <set>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/field.h"

namespace tank_hero::visualizer {
using ci::app::KeyEvent;
using glm::vec2;

constexpr int kWindowSize = 1000;

class TankHeroApp : public ci::app::App {
 public:
  TankHeroApp();

  void draw() override;
  void update() override;
  void keyDown(KeyEvent event) override;
  void keyUp(KeyEvent event) override;

 private:

  // data members
  std::set<int> held_keys_;
  Field field_;
};

}  // namespace tank_hero::visualizer
#endif  // TANK_HERO_TANK_HERO_APP_H
