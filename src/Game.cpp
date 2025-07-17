#include <SFML/Window/VideoMode.hpp>

#include "Game.hpp"

Game::Game()
    : mWindow(sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Eagle Game")),
      mPlayer(40.f) {

  mWindow.setFramerateLimit(144);

  mPlayer.setPosition({100.f, 100.f});
  mPlayer.setFillColor(sf::Color::Red);
}

void Game::run() {

  while (mWindow.isOpen()) {
    processEvent();
    update();
    render();
  }
}

void Game::processEvent() {
  while (const std::optional event = mWindow.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }
  }
}

void Game::update() {}

void Game::render() {
  mWindow.clear();
  mWindow.draw(mPlayer);
  mWindow.display();
}
