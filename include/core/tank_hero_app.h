//
// Created by Jun Lee on 11/13/20.
//

#ifndef TANK_HERO_TANK_HERO_APP_H
#define TANK_HERO_TANK_HERO_APP_H

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace tank_hero::visualizer {

class TankHeroApp : public ci::app::App {
 public:
  TankHeroApp();
};

}  // namespace tank_hero::visualizer
#endif  // TANK_HERO_TANK_HERO_APP_H
