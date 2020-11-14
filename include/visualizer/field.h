//
// Created by Jun Lee on 11/14/20.
//

#ifndef TANK_HERO_FIELD_H
#define TANK_HERO_FIELD_H
#include "core/tank.h"
namespace tank_hero::visualizer {
class Field {
 public:
  Field();

 private:
  Tank tank_;
};
}  // namespace tank_hero::visualizer
#endif  // TANK_HERO_FIELD_H
