#include <SFML/Graphics/RenderWindow.hpp>

#include <TitleState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

TitleState::TitleState(StateStack &stack, Context context)
	: State(stack, context), mBackgroundSprite(context.textures->get(Textures::TitleScreen)), mText(context.fonts->get(Fonts::Main), "Press any key to start", 30), mShowText(true), mTextEffectTime(sf::Time::Zero)
{
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
	sf::RenderWindow &window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);
}

bool TitleState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event &event)
{
	// If any key is pressed, trigger the next screen
	if (event.is<sf::Event::KeyPressed>())
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}