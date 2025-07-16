#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Eagle Game");
  window.setFramerateLimit(144);

  sf::CircleShape shape(40.f);
  shape.setPosition({100.f, 100.f});
  shape.setFillColor(sf::Color::Red);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();

    window.draw(shape);

    window.display();
  }
}
