#include <Aircraft.hpp>
#include <ResourceHolder.hpp>

Textures::ID toTextureID(Aircraft::Type type)
{
  switch (type)
  {
  case Aircraft::Eagle:
    return Textures::Eagle;

  case Aircraft::Raptor:
    return Textures::Raptor;

  default:
    throw std::runtime_error("Unknown game type");
  }
}

Aircraft::Aircraft(Type type, const TextureHolder &textures)
    : mType(type), mSprite(textures.get(toTextureID(type)))
{
  sf::FloatRect bounds = mSprite.getLocalBounds();
  mSprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

void Aircraft::drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const
{
  target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
  switch (mType)
  {
  case Eagle:
    return Category::PlayerAircraft;

  default:
    return Category::EnemyAircraft;
  }
}
