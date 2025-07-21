#ifndef TEXTNODE_HPP
#define TEXTNODE_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <SceneNode.hpp>

class TextNode : public SceneNode
{
public:
	explicit TextNode(const FontHolder &fonts, const std::string &text);

	void setString(const std::string &text);

private:
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	sf::Text mText;
};

#endif // TEXTNODE_HPP
