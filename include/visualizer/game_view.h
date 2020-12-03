#ifndef TANK_HERO_GAME_VIEW_H
#define TANK_HERO_GAME_VIEW_H

#include "cinder/Font.h"
#include "cinder/gl/gl.h"
#include "core/game.h"

namespace tank_hero::visualizer {
using ci::app::loadAsset;
using ci::gl::Texture2d;
using ci::gl::Texture2dRef;

const ci::Color kBulletColor("black");
const ci::Color kObstacleColor("saddlebrown");
const ci::Color kTextColor("white");
const ci::Color kGameOverColor("red");

const ci::Font kTextFont("Arial", 20);
const ci::Font kGameOverFont("Arial", 50);

const size_t kTextMargin = 30;
const size_t kHeartImgWidth = 20;

class GameView {
 public:
  explicit GameView(const Game* game, size_t window_size,
                    const vec2* camera_offset);

  /// Draws all game objects and texts showing game status
  void Draw() const;

 private:
  void DrawTank() const;
  void DrawEnemies() const;
  void DrawBullets() const;
  void DrawObstacles() const;
  void DisplayGameStatus() const;
  void DrawGameEndScreen() const;

  void DrawRotatedImage(const Texture2dRef& image, const vec2& position,
                        const vec2& direction) const;

  /// Returns rotation(angle between up vector and the direction) given
  /// direction as below.
  ///            0
  ///    7/4 pi     pi/4
  /// 3/2 pi     x      pi/2
  ///    5/4 pi     3/4 pi
  ///            pi
  float CalcRotation(const vec2& direction) const;

  const Game* game_;
  const vec2* camera_offset_;
  const size_t window_size_;

  // images
  Texture2dRef heart_img_;
  Texture2dRef bomb_img_;
  Texture2dRef gun_img_;
  Texture2dRef shield_img_;
  Texture2dRef tank_body_img_;
  Texture2dRef tank_gun_img_;
  Texture2dRef tank_bullet_img_;
  Texture2dRef melee_enemy_img_;
  Texture2dRef ranged_enemy_img_;
  void DrawItems() const;
};
}  // namespace tank_hero::visualizer

#endif  // TANK_HERO_GAME_VIEW_H
