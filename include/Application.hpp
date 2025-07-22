#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <Player.hpp>
#include <StateStack.hpp>

class Application
{
public:
	Application();
	void run();

private:
	void processInput();
	void update(sf::Time dt);
	void render();

	void updateStatistics(sf::Time dt);
	void registerStates();

private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	TextureHolder mTextures;
	FontHolder mFonts;
	sf::Font mFont;
	Player mPlayer;

	MusicPlayer mMusic;
	SoundPlayer mSounds;
	StateStack mStateStack;

	std::unique_ptr<sf::Text> mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;
};

#endif // APPLICATION_HPP
