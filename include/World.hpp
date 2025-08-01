#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <Aircraft.hpp>
#include <CommandQueue.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <SceneNode.hpp>
#include <BloomEffect.hpp>
#include <SoundPlayer.hpp>

// Forward declaration
namespace sf
{
  class RenderTarget;
}

class World
{
private:
  enum Layer
  {
    Background,
    LowerAir,
    UpperAir,
    LayerCount
  };

  struct SpawnPoint
  {
    SpawnPoint(Aircraft::Type type, float x, float y)
        : type(type), x(x), y(y)
    {
    }

    Aircraft::Type type;
    float x;
    float y;
  };

public:
  World(sf::RenderTarget &outputTarget, FontHolder &fonts, SoundPlayer &sounds);
  void update(sf::Time dt);
  void draw();

  CommandQueue &getCommandQueue();

  bool hasAlivePlayer() const;
  bool hasPlayerReachedEnd() const;

private:
  void loadTextures();
  void adaptPlayerPosition();
  void adaptPlayerVelocity();
  void handleCollisions();
  void updateSounds();

  void buildScene();
  void addEnemies();
  void addEnemy(Aircraft::Type type, float relX, float relY);
  void spawnEnemies();
  void destroyEntitiesOutsideView();
  void guideMissiles();
  sf::FloatRect getViewBounds() const;
  sf::FloatRect getBattlefieldBounds() const;

private:
  sf::RenderTarget &mTarget;
  sf::RenderTexture mSceneTexture;
  sf::View mWorldView;
  TextureHolder mTextures;
  FontHolder &mFonts;
  SoundPlayer &mSounds;

  SceneNode mSceneGraph;
  std::array<SceneNode *, LayerCount> mSceneLayers;
  CommandQueue mCommandQueue;

  sf::FloatRect mWorldBounds;
  sf::Vector2f mSpawnPosition;
  float mScrollSpeed;
  Aircraft *mPlayerAircraft;

  std::vector<SpawnPoint> mEnemySpawnPoints;
  std::vector<Aircraft *> mActiveEnemies;

  BloomEffect mBloomEffect;
};

#endif // WORLD_HPP
