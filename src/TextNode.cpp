#include <SFML/Graphics/RenderTarget.hpp>

#include <TextNode.hpp>
#include <Utility.hpp>

TextNode::TextNode(const FontHolder &fonts, const std::string &text)
	: mText(fonts.get(Fonts::Main), text, 20)
{
	setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(mText, states);
}

void TextNode::setString(const std::string &text)
{
	mText.setString(text);
	centerOrigin(mText);
}