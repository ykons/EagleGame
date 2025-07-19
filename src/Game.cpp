#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <Game.hpp>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::RenderWindow(sf::VideoMode({640u, 480u}), "Eagle Game")),
      mWorld(mWindow), mFont("assets/Sansation.ttf"), mStatisticsText(mFont),
      mStatisticsUpdateTime(sf::Time::Zero) {

  mStatisticsText.setFillColor(sf::Color::White);
  mStatisticsText.setPosition({10.f, 10.f});
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (mWindow.isOpen()) {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;

    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      processEvents();
      update(TimePerFrame);
    }

    updateStatistics(elapsedTime);
    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = mWindow.pollEvent()) {
    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      handlePlayerInput(keyPressed->code, true);
    } else if (const auto *keyReleased =
                   event->getIf<sf::Event::KeyReleased>()) {
      handlePlayerInput(keyReleased->code, false);
    } else if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }
  }
}

void Game::update(sf::Time elapsedTime) { mWorld.update(elapsedTime); }

void Game::render() {
  mWindow.clear();

  mWorld.draw();

  mWindow.setView(mWindow.getDefaultView());

  mWindow.draw(mStatisticsText);
  mWindow.display();
}

void Game::updateStatistics(sf::Time deltaTime) {
  mStatisticsUpdateTime += deltaTime;
  ++mStatisticsNumFrames;

  if (mStatisticsUpdateTime >= sf::seconds(1.f)) {
    mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));
    mStatisticsUpdateTime -= sf::seconds(1.f);
    mStatisticsNumFrames = 0;
  }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {}
