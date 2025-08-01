#ifndef SOUNDPLAYER_HPP
#define SOUNDPLAYER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <list>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

class SoundPlayer
{
public:
	SoundPlayer();

	void play(SoundEffect::ID effect);
	void play(SoundEffect::ID effect, sf::Vector2f position);

	void removeStoppedSounds();
	void setListenerPosition(sf::Vector2f position);
	sf::Vector2f getListenerPosition() const;

private:
	SoundBufferHolder mSoundBuffers;
	std::list<sf::Sound> mSounds;
};

#endif // SOUNDPLAYER_HPP
