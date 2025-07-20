#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <MenuState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mOptions()
, mOptionIndex(0)
, mBackgroundSprite(context.textures->get(Textures::TitleScreen))
{
	sf::Font& font = context.fonts->get(Fonts::Main);

	// A simple menu demonstration
	sf::Text playOption(font, "Play", 30);
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption(font, "Exit", 30);
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(exitOption);

	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	for (const sf::Text& text : mOptions)
		window.draw(text);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if (!event.is<sf::Event::KeyPressed>())
		return false;

	if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::Loading);
		}
		else if (mOptionIndex == Exit)
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
		}
	}

	else if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up)
	{
		// Decrement and wrap-around
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}

	else if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down)
	{
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (mOptions.empty())
		return;

	// White all texts
	for (sf::Text& text : mOptions)
		text.setFillColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}
