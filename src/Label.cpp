#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <Label.hpp>
#include <Utility.hpp>

namespace GUI
{

	Label::Label(const std::string &text, const FontHolder &fonts)
		: mText(fonts.get(Fonts::Main), text, 16)
	{
	}

	bool Label::isSelectable() const
	{
		return false;
	}

	void Label::handleEvent(const sf::Event &)
	{
	}

	void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}

	void Label::setText(const std::string &text)
	{
		mText.setString(text);
	}

}