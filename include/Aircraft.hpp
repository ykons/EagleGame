#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>

class Aircraft : public Entity {
public:
  enum Type { Eagle, Raptor };

public:
  explicit Aircraft(Type type, const TextureHolder &textures);

  virtual unsigned int getCategory() const;

private:
  virtual void drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const;

private:
  Type mType;
  sf::Sprite mSprite;
};

#endif // AIRCRAFT_HPP
