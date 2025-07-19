#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <Aircraft.hpp>
#include <CommandQueue.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <SceneNode.hpp>

class World {
private:
  enum Layer { Background, Air, LayerCount };

public:
  explicit World(sf::RenderWindow &window);
  void update(sf::Time dt);
  void draw();

  CommandQueue &getCommandQueue();

private:
  void loadTextures();
  void buildScene();
  void adaptPlayerPosition();
  void adaptPlayerVelocity();

private:
  sf::RenderWindow &mWindow;
  sf::View mWorldView;
  TextureHolder mTextures;

  SceneNode mSceneGraph;
  std::array<SceneNode *, LayerCount> mSceneLayers;
  CommandQueue mCommandQueue;

  sf::FloatRect mWorldBounds;
  sf::Vector2f mSpawnPosition;
  float mScrollSpeed;
  Aircraft *mPlayerAircraft;
};

#endif // WORLD_HPP
