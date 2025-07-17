#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Game {

public:
  Game();
  void run();

private:
  void processEvents();
  void update(sf::Time deltaTime);
  void render();
  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
  static const float PlayerSpeed;
  static const sf::Time TimePerFrame;

  sf::RenderWindow mWindow;

  sf::Texture mTexture;
  sf::Sprite mPlayer;

  bool mIsMovingUp = false;
  bool mIsMovingDown = false;
  bool mIsMovingLeft = false;
  bool mIsMovingRight = false;
};
