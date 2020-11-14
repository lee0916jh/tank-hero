#include "visualizer/field.h"

namespace tank_hero::visualizer {

Field::Field() : width_(kFieldWidth), tank_(kSpawnPoint) {}

void Field::HandleKeyInputs(const std::set<int>& keys) {
  bool a_pressed = false, s_pressed = false, d_pressed = false,
       w_pressed = false;
  for (int key : keys) {
    if (key == KeyEvent::KEY_a) a_pressed = true;
    if (key == KeyEvent::KEY_s) s_pressed = true;
    if (key == KeyEvent::KEY_d) d_pressed = true;
    if (key == KeyEvent::KEY_w) w_pressed = true;
  }

  if (w_pressed) tank_.MoveUp();
  if (a_pressed) tank_.MoveLeft();
  if (d_pressed) tank_.MoveRight();
  if (s_pressed) tank_.MoveDown();
}

void Field::Draw() { DrawTank(); }

void Field::DrawTank() {
  ci::Color("green");
  ci::gl::drawSolidCircle(tank_.GetPosition(), 10);
}
}  // namespace tank_hero::visualizer