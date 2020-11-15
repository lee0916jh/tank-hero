#include "visualizer/tank_hero_app.h"
namespace tank_hero::visualizer {
TankHeroApp::TankHeroApp() {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void TankHeroApp::update() {
  game_.HandleKeyInputs(held_keys_);
  game_.Update();
}

void TankHeroApp::draw() {
  ci::Color8u background_color(ci::Color("grey"));
  ci::gl::clear(background_color);

  game_.Draw();
}

void TankHeroApp::keyDown(KeyEvent event) {
  held_keys_.insert(event.getCode());
}

void TankHeroApp::keyUp(KeyEvent event) { held_keys_.erase(event.getCode()); }
void TankHeroApp::mouseDown(MouseEvent event) {
  game_.FireBullet(event.getPos());
}

}  // namespace tank_hero::visualizer
