#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <SpriteNode.hpp>
#include <World.hpp>

World::World(sf::RenderWindow &window)
    : mWindow(window), mWorldView(window.getDefaultView()), mTextures(),
      mSceneGraph(), mSceneLayers(),
      mWorldBounds({0.f, 0.f}, {mWorldView.getSize().x, 2000.f}),
      mSpawnPosition(mWorldView.getSize().x / 2.f,
                     mWorldBounds.size.y - mWorldView.getSize().y / 2.f),
      mScrollSpeed(-50.f), mPlayerAircraft(nullptr) {
  loadTextures();
  buildScene();

  mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt) {
  // Scroll the world
  mWorldView.move({0.f, mScrollSpeed * dt.asSeconds()});

  // Move the player sidewards (plane scouts follow the main aircraft)
  sf::Vector2f position = mPlayerAircraft->getPosition();
  sf::Vector2f velocity = mPlayerAircraft->getVelocity();

  // If player touches borders, flip its X velocity
  if (position.x <= mWorldBounds.position.x + 150.f ||
      position.x >= mWorldBounds.position.x + mWorldBounds.size.x - 150.f) {
    velocity.x = -velocity.x;
    mPlayerAircraft->setVelocity(velocity);
  }

  // Apply movements
  mSceneGraph.update(dt);
}

void World::draw() {
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
}

void World::loadTextures() {
  mTextures.load(Textures::Eagle, "assets/textures/Eagle.png");
  mTextures.load(Textures::Raptor, "assets/textures/Raptor.png");
  mTextures.load(Textures::Desert, "assets/textures/Desert.png");
}

void World::buildScene() {
  // Initialize the different layers
  for (std::size_t i = 0; i < LayerCount; ++i) {
    SceneNode::Ptr layer(new SceneNode());
    mSceneLayers[i] = layer.get();

    mSceneGraph.attachChild(std::move(layer));
  }

  // Prepare the tiled background
  sf::Texture &texture = mTextures.get(Textures::Desert);
  sf::IntRect textureRect(mWorldBounds);
  texture.setRepeated(true);

  // Add the background sprite to the scene
  std::unique_ptr<SpriteNode> backgroundSprite(
      new SpriteNode(texture, textureRect));
  backgroundSprite->setPosition(
      {mWorldBounds.position.x, mWorldBounds.position.y});
  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

  // Add player's aircraft
  std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
  mPlayerAircraft = leader.get();
  mPlayerAircraft->setPosition(mSpawnPosition);
  mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
  mSceneLayers[Air]->attachChild(std::move(leader));

  // Add two escorting aircrafts, placed relatively to the main plane
  std::unique_ptr<Aircraft> leftEscort(
      new Aircraft(Aircraft::Raptor, mTextures));
  leftEscort->setPosition({-80.f, 50.f});
  mPlayerAircraft->attachChild(std::move(leftEscort));

  std::unique_ptr<Aircraft> rightEscort(
      new Aircraft(Aircraft::Raptor, mTextures));
  rightEscort->setPosition({80.f, 50.f});
  mPlayerAircraft->attachChild(std::move(rightEscort));
}
