#include "visualizer/tank_hero_app.h"
namespace tank_hero::visualizer {
TankHeroApp::TankHeroApp() : tank_(kSpawnPoint) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void TankHeroApp::update() {}
void TankHeroApp::draw() {
  ci::Color8u background_color(ci::Color("grey"));
  ci::gl::clear(background_color);
}

void TankHeroApp::keyDown(KeyEvent event) {
  held_keys_.insert(event.getCode());
}

void TankHeroApp::keyUp(KeyEvent event) { held_keys_.erase(event.getCode()); }

void TankHeroApp::HandleKeyInputs() {
  bool a_pressed = false, s_pressed = false, d_pressed = false,
       w_pressed = false;
  for (int key_code : held_keys_) {
    if (key_code == KeyEvent::KEY_a) a_pressed = true;
    if (key_code == KeyEvent::KEY_s) s_pressed = true;
    if (key_code == KeyEvent::KEY_d) d_pressed = true;
    if (key_code == KeyEvent::KEY_w) w_pressed = true;
  }

  if (a_pressed && w_pressed) {
    tank_.Move
  } else if (w_pressed && d_pressed) {
    tank_.Move("right");
  } else if (s_pressed && d_pressed) {
    tank_.Move("right");
  } else if (a_pressed && s_pressed) {
    tank_.Move("right");
  } else if (w_pressed) {
    tank_.Move("right");
  } else if (s_pressed) {
    tank_.Move("right");
  } else if (a_pressed) {
    tank_.Move("right");
  } else if (d_pressed) {
    tank_.Move("right");
  }
}
}  // namespace tank_hero::visualizer
