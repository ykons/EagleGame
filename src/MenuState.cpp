#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <MenuState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>
#include <Button.hpp>

MenuState::MenuState(StateStack &stack, Context context)
	: State(stack, context), mBackgroundSprite(context.textures->get(Textures::TitleScreen)), mGUIContainer()
{
	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition({100, 250});
	playButton->setText("Play");
	playButton->setCallback([this]()
							{
		requestStackPop();
		requestStackPush(States::Game); });

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setPosition({100, 300});
	settingsButton->setText("Settings");
	settingsButton->setCallback([this]()
								{ requestStackPush(States::Settings); });

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition({100, 350});
	exitButton->setText("Exit");
	exitButton->setCallback([this]()
							{ requestStackPop(); });

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(exitButton);
}

void MenuState::draw()
{
	sf::RenderWindow &window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event &event)
{
	mGUIContainer.handleEvent(event);

	if (event.is<sf::Event::KeyPressed>())
	{
		if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
		{
			requestStackPop();
			return true;
		}
	}

	return false;
}