#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

class MusicPlayer
{
public:
	MusicPlayer();

	void play(Music::ID theme);
	void stop();

	void setPaused(bool paused);
	void setVolume(float volume);

private:
	sf::Music mMusic;
	std::map<Music::ID, std::string> mFilenames;
	float mVolume;
};

#endif // MUSICPLAYER_HPP
