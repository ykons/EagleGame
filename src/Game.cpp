#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Game.hpp"

const float Game::PlayerSpeed = 200.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Eagle Game")),
      mTexture("assets/textures/Eagle.png"), mPlayer(mTexture),
      mFont("assets/Sansation.ttf"), mStatisticsText(mFont),
      mStatisticsUpdateTime(sf::Time::Zero) {
  mPlayer.setPosition({100.f, 100.f});

  mStatisticsText.setFillColor(sf::Color::White);
  mStatisticsText.setPosition({10.f, 10.f});
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (mWindow.isOpen()) {
    processEvents();
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

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
  if (key == sf::Keyboard::Key::W) {
    mIsMovingUp = isPressed;
  } else if (key == sf::Keyboard::Key::S) {
    mIsMovingDown = isPressed;
  } else if (key == sf::Keyboard::Key::A) {
    mIsMovingLeft = isPressed;
  } else if (key == sf::Keyboard::Key::D) {
    mIsMovingRight = isPressed;
  }
}

void Game::update(sf::Time deltaTime) {
  sf::Vector2f movement({0.f, 0.f});

  if (mIsMovingUp) {
    movement.y -= PlayerSpeed * deltaTime.asSeconds();
  }
  if (mIsMovingDown) {
    movement.y += PlayerSpeed * deltaTime.asSeconds();
  }
  if (mIsMovingLeft) {
    movement.x -= PlayerSpeed * deltaTime.asSeconds();
  }
  if (mIsMovingRight) {
    movement.x += PlayerSpeed * deltaTime.asSeconds();
  }

  mPlayer.move(movement);
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

void Game::render() {
  mWindow.clear();
  mWindow.draw(mPlayer);
  mWindow.draw(mStatisticsText);
  mWindow.display();
}
