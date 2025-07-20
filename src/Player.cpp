#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <map>
#include <string>

#include <Aircraft.hpp>
#include <CommandQueue.hpp>
#include <Player.hpp>

struct AircraftMover
{
  AircraftMover(float vx, float vy) : velocity(vx, vy) {}

  void operator()(Aircraft &aircraft, sf::Time) const
  {
    aircraft.accelerate(velocity);
  }

  sf::Vector2f velocity;
};

Player::Player()
{
  // Set initial key bindings
  mKeyBinding[sf::Keyboard::Key::Left] = MoveLeft;
  mKeyBinding[sf::Keyboard::Key::Right] = MoveRight;
  mKeyBinding[sf::Keyboard::Key::Up] = MoveUp;
  mKeyBinding[sf::Keyboard::Key::Down] = MoveDown;

  // Set initial action bindings
  initializeActions();

  // Assign all categories to player's aircraft
  for (auto &pair : mActionBinding)
    pair.second.category = Category::PlayerAircraft;
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands)
{
  if (event.is<sf::Event::KeyPressed>())
  {
    // Check if pressed key appears in key binding, trigger command if so
    auto found = mKeyBinding.find(event.getIf<sf::Event::KeyPressed>()->code);
    if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
      commands.push(mActionBinding[found->second]);
  }
}

void Player::handleRealtimeInput(CommandQueue &commands)
{
  // Traverse all assigned keys and check if they are pressed
  for (auto &pair : mKeyBinding)
  {
    // If key is pressed, lookup action and trigger corresponding command
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
      commands.push(mActionBinding[pair.second]);
  }
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
  // Remove all keys that already map to action
  for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
  {
    if (itr->second == action)
      mKeyBinding.erase(itr++);
    else
      ++itr;
  }

  // Insert new binding
  mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
  for (auto pair : mKeyBinding)
  {
    if (pair.second == action)
      return pair.first;
  }

  return sf::Keyboard::Key::Unknown;
}

void Player::initializeActions()
{
  const float playerSpeed = 200.f;

  mActionBinding[MoveLeft].action =
      derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
  mActionBinding[MoveRight].action =
      derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
  mActionBinding[MoveUp].action =
      derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
  mActionBinding[MoveDown].action =
      derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
}

bool Player::isRealtimeAction(Action action)
{
  switch (action)
  {
  case MoveLeft:
  case MoveRight:
  case MoveDown:
  case MoveUp:
    return true;

  default:
    return false;
  }
}
