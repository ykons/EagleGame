#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <vector>

#include <Command.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable {
public:
  typedef std::unique_ptr<SceneNode> Ptr;

public:
  SceneNode();

  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode &node);

  void update(sf::Time dt);

  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;

  void onCommand(const Command &command, sf::Time dt);
  virtual unsigned int getCategory() const;

private:
  virtual void updateCurrent(sf::Time dt);
  void updateChildren(sf::Time dt);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const final;
  virtual void drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const;
  void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

private:
  std::vector<Ptr> mChildren;
  SceneNode *mParent;
};

#endif // SCENENODE_HPP
