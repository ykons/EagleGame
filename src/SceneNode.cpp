#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <algorithm>
#include <cassert>

#include <SceneNode.hpp>
#include <Utility.hpp>
#include <Command.hpp>

SceneNode::SceneNode(Category::Type category) : mChildren(), mParent(nullptr), mDefaultCategory(category) {}

void SceneNode::attachChild(Ptr child)
{
  child->mParent = this;
  mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node)
{
  auto found = std::find_if(mChildren.begin(), mChildren.end(),
                            [&](Ptr &p) -> bool
                            { return p.get() == &node; });
  assert(found != mChildren.end());

  Ptr result = std::move(*found);
  result->mParent = nullptr;
  mChildren.erase(found);

  return result;
}

void SceneNode::update(sf::Time dt, CommandQueue &commands)
{
  updateCurrent(dt, commands);
  updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue &commands)
{
  // Default implementation (can be overridden in derived classes)
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue &commands)
{
  for (const Ptr &child : mChildren)
  {
    child->update(dt, commands);
  }
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Apply transform of current node
  states.transform *= getTransform();

	// Draw node and children with changed transform
  drawCurrent(target, states);
  drawChildren(target, states);

  // Draw bounding rectangle - disabled by default
  drawBoundingRect(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget &, sf::RenderStates) const {}

void SceneNode::drawChildren(sf::RenderTarget &target,
                             sf::RenderStates states) const
{
  for (const Ptr &child : mChildren)
  {
    child->draw(target, states);
  }
}

void SceneNode::drawBoundingRect(sf::RenderTarget &target, sf::RenderStates) const
{
  sf::FloatRect rect = getBoundingRect();

  sf::RectangleShape shape;
  shape.setPosition(sf::Vector2f(rect.position.x, rect.position.y));
  shape.setSize(sf::Vector2f(rect.size.x, rect.size.y));
  shape.setFillColor(sf::Color::Transparent);
  shape.setOutlineColor(sf::Color::Green);
  shape.setOutlineThickness(1.f);

  target.draw(shape);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
  return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
  sf::Transform transform = sf::Transform::Identity;

  for (const SceneNode *node = this; node != nullptr; node = node->mParent)
    transform = node->getTransform() * transform;

  return transform;
}

void SceneNode::onCommand(const Command &command, sf::Time dt)
{
  // Command current node, if category matches
  if (command.category & getCategory())
    command.action(*this, dt);

  // Command children
  for (const Ptr &child : mChildren)
  {
    child->onCommand(command, dt);
  }
}

unsigned int SceneNode::getCategory() const { return mDefaultCategory; }

void SceneNode::checkSceneCollision(SceneNode &sceneGraph, std::set<Pair> &collisionPairs)
{
  checkNodeCollision(sceneGraph, collisionPairs);

  for (const Ptr &child : sceneGraph.mChildren)
  {
    checkNodeCollision(*child, collisionPairs);
  }
}

void SceneNode::checkNodeCollision(SceneNode &node, std::set<Pair> &collisionPairs)
{
  if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
    collisionPairs.insert(std::minmax(this, &node));

  for (const Ptr &child : mChildren)
  {
    child->checkNodeCollision(node, collisionPairs);
  }
}

void SceneNode::removeWrecks()
{
  // Remove all children which request so
  auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
  mChildren.erase(wreckfieldBegin, mChildren.end());

  // Call function recursively for all remaining children
  std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

sf::FloatRect SceneNode::getBoundingRect() const
{
  return sf::FloatRect();
}

bool SceneNode::isMarkedForRemoval() const
{
  // By default, remove node if entity is destroyed
  return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
  // By default, scene node needn't be removed
  return false;
}

bool collision(const SceneNode &lhs, const SceneNode &rhs)
{
  if (lhs.getCategory() == Category::Aircraft || rhs.getCategory() == Category::EnemyAircraft)
    return false;

  bool isColliding = lhs.getBoundingRect().findIntersection(rhs.getBoundingRect()).has_value();

  if (isColliding)
  {
    // Check if the bounding rectangles intersect
    sf::FloatRect intersection = lhs.getBoundingRect().findIntersection(rhs.getBoundingRect()).value();
  }

  return isColliding;
}

float distance(const SceneNode &lhs, const SceneNode &rhs)
{
  return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}
