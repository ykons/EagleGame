#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <PauseState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

PauseState::PauseState(StateStack &stack, Context context)
	: State(stack, context)
	  // , mBackgroundSprite()
	  ,
	  mPausedText(context.fonts->get(Fonts::Main), "Game Paused", 70), mInstructionText(context.fonts->get(Fonts::Main), "(Press Backspace to return to the main menu)", 30)
{
	sf::Vector2f viewSize = context.window->getView().getSize();

	centerOrigin(mPausedText);
	mPausedText.setPosition({0.5f * viewSize.x, 0.4f * viewSize.y});

	centerOrigin(mInstructionText);
	mInstructionText.setPosition({0.5f * viewSize.x, 0.6f * viewSize.y});
}

void PauseState::draw()
{
	sf::RenderWindow &window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event &event)
{
	if (!event.is<sf::Event::KeyPressed>())
		return false;

	if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
	{
		// Escape pressed, remove itself to return to the game
		requestStackPop();
	}

	if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Backspace)
	{
		// Escape pressed, remove itself to return to the game
		requestStateClear();
		requestStackPush(States::Menu);
	}

	return false;
}