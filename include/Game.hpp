#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <cstddef>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class Game {
public:
  enum Type { Eagle, Desert };

public:
  Game(TextureHolder &textures);
  void run();

private:
  void processEvents();
  void update(sf::Time deltaTime);
  void render();

  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
  void updateStatistics(sf::Time deltaTime);

private:
  static const float PlayerSpeed;
  static const sf::Time TimePerFrame;

  sf::RenderWindow mWindow;

  
  sf::Sprite mPlayer;
  sf::Font mFont;
  sf::Text mStatisticsText;
  sf::Time mStatisticsUpdateTime;

  std::size_t mStatisticsNumFrames = 0;

  bool mIsMovingUp = false;
  bool mIsMovingDown = false;
  bool mIsMovingLeft = false;
  bool mIsMovingRight = false;

  Type mType;
  TextureHolder &mTextures;
};
