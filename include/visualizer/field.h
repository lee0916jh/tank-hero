#ifndef TANK_HERO_FIELD_H
#define TANK_HERO_FIELD_H
#include <set>

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

#include "core/tank.h"
namespace tank_hero::visualizer {
using ci::app::KeyEvent;

constexpr float kFieldWidth = 10000;
const vec2 kSpawnPoint = vec2(100, 100);

class Field {
 public:
  Field();

  void Draw();
  void HandleKeyInputs(const std::set<int>& keys);

 private:
  void DrawTank();

  //member variables
  float width_;
  Tank tank_;
};
}  // namespace tank_hero::visualizer
#endif  // TANK_HERO_FIELD_H
