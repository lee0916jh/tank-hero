#include "visualizer/button.h"

namespace tank_hero::visualizer {
Button::Button(const std::string& text, const vec2& center, float width, float height,
               const ci::Color& text_color, const ci::Color& bg_color)
    : text_(text),
      center_(center),
      width_(width),
      height_(height),
      text_color_(text_color),
      bg_color_(bg_color) {}

void Button::Draw(float corner_radius) {
  ci::gl::color(bg_color_);
  vec2 offset(width_ / 2, height_ / 2);
  ci::gl::drawStrokedRect(ci::Rectf(center_ - offset, center_ + offset));

  ci::gl::color(text_color_);
  ci::gl::drawStringCentered(text_, center_);
}

bool Button::CheckClicked(vec2 mouse_pos) {
  return mouse_pos.x > (center_.x - width_ / 2) &&
         mouse_pos.x < (center_.x + width_ / 2) &&
         mouse_pos.y > (center_.y - height_ / 2) &&
         mouse_pos.y < (center_.y + height_ / 2);
}
}  // namespace tank_hero::visualizer
