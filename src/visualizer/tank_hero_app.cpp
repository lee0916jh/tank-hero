#include "visualizer/tank_hero_app.h"
namespace tank_hero::visualizer {
TankHeroApp::TankHeroApp() {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void TankHeroApp::update() { field_.HandleKeyInputs(held_keys_); }
void TankHeroApp::draw() {
  ci::Color8u background_color(ci::Color("grey"));
  ci::gl::clear(background_color);

  field_.Draw();
}

void TankHeroApp::keyDown(KeyEvent event) {
  held_keys_.insert(event.getCode());
}

void TankHeroApp::keyUp(KeyEvent event) { held_keys_.erase(event.getCode()); }

}  // namespace tank_hero::visualizer
