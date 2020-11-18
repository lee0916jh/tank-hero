#include <visualizer//tank_hero_app.h>

using tank_hero::app::TankHeroApp;

void prepareSettings(TankHeroApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(TankHeroApp, ci::app::RendererGl, prepareSettings);