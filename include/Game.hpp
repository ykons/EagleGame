#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <cstddef>

#include <World.hpp>

class Game {
public:
  Game();
  void run();

private:
  void processEvents();
  void update(sf::Time elapsedTime);
  void render();

  void updateStatistics(sf::Time deltaTime);

private:
  static const sf::Time TimePerFrame;

  sf::RenderWindow mWindow;
  World mWorld;
  Player mPlayer;

  sf::Font mFont;
  sf::Text mStatisticsText;
  sf::Time mStatisticsUpdateTime;
  std::size_t mStatisticsNumFrames = 0;
};

#endif // GAME_HPP
