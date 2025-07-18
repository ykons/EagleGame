#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Game.hpp"

void loadTextures(TextureHolder &textures) {
  textures.load(Textures::Eagle, "assets/textures/Eagle.png");
  textures.load(Textures::Desert, "assets/textures/Desert.png");
}

int main() {
  TextureHolder textures;
  loadTextures(textures);
  Game game(textures);
  game.run();
}
