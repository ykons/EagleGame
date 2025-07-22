#include <Application.hpp>
#include <State.hpp>
#include <StateIdentifiers.hpp>
#include <TitleState.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <PauseState.hpp>
#include <LoadingState.hpp>
#include <SettingsState.hpp>
#include <GameOverState.hpp>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: mWindow(sf::RenderWindow(sf::VideoMode({1024, 768}), "Eagle Game", sf::Style::Close)), mTextures(), mFonts(), mPlayer(), mMusic(), mSounds(), mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusic, mSounds)), mStatisticsText(nullptr), mStatisticsUpdateTime(), mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);

	mFonts.load(Fonts::Main, "assets/Sansation.ttf");

	mTextures.load(Textures::TitleScreen, "assets/textures/TitleScreen.png");
	mTextures.load(Textures::Buttons, "assets/textures/Buttons.png");

	mStatisticsText = std::make_unique<sf::Text>(mFonts.get(Fonts::Main), "", 10u);
	mStatisticsText->setPosition({5.f, 5.f});

	registerStates();
	mStateStack.pushState(States::Title);

	mMusic.setVolume(25.f);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	while (const std::optional<sf::Event> event = mWindow.pollEvent())
	{
		mStateStack.handleEvent(*event);

		if (event->is<sf::Event::Closed>())
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(*mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText->setString("FPS: " + std::to_string(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<LoadingState>(States::Loading);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<SettingsState>(States::Settings);
	mStateStack.registerState<GameOverState>(States::GameOver);
}
