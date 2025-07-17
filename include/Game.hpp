#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game {

public:
  Game();
  void run();

private:
  void processEvent();
  void update();
  void render();

private:
  sf::RenderWindow mWindow;
  sf::CircleShape mPlayer;
};
