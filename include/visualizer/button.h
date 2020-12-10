#ifndef TANK_HERO_BUTTON_H
#define TANK_HERO_BUTTON_H

#include <optional>
#include <string>

#include "cinder/gl/gl.h"

namespace tank_hero::visualizer {
using ci::vec2;

class Button {
 public:
  Button(const std::string& text, const vec2& center, float width, float height,
         const ci::Color& text_color = ci::Color("black"),
         const ci::Color& bg_color = ci::Color("white"));

  /// Draws a rectangular button.
  /// \param corner_radius Optional parameter that can be passed to draw a
  ///                      rounded button
  void Draw(float corner_radius = 0);

  /// Checks if the user clicked this button and returns the result.
  /// \param mouse_pos mouse position to compare with this button's position.
  /// \return true only if the mouse click happened on the button.
  bool CheckClicked(vec2 mouse_pos);

 private:
  std::string text_;
  vec2 center_;
  float width_;
  float height_;
  ci::Color text_color_;
  ci::Color bg_color_;
};

}  // namespace tank_hero::visualizer

#endif  // TANK_HERO_BUTTON_H
