#include <SFML/Audio/Listener.hpp>

#include <cmath>

#include <SoundPlayer.hpp>

namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

SoundPlayer::SoundPlayer()
	: mSoundBuffers(), mSounds()
{
	mSoundBuffers.load(SoundEffect::AlliedGunfire, "assets/sound/AlliedGunfire.wav");
	mSoundBuffers.load(SoundEffect::EnemyGunfire, "assets/sound/EnemyGunfire.wav");
	mSoundBuffers.load(SoundEffect::Explosion1, "assets/sound/Explosion1.wav");
	mSoundBuffers.load(SoundEffect::Explosion2, "assets/sound/Explosion2.wav");
	mSoundBuffers.load(SoundEffect::LaunchMissile, "assets/sound/LaunchMissile.wav");
	mSoundBuffers.load(SoundEffect::CollectPickup, "assets/sound/CollectPickup.wav");
	mSoundBuffers.load(SoundEffect::Button, "assets/sound/Button.wav");

	// Listener points towards the screen (default in SFML)
	sf::Listener::setDirection({0.f, 0.f, -1.f});
}

void SoundPlayer::play(SoundEffect::ID effect)
{
	play(effect, getListenerPosition());
}

void SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position)
{
	mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
	sf::Sound &sound = mSounds.back();

	sound.setPosition({position.x, -position.y, 0.f});
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);

	sound.play();
}

void SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if([](const sf::Sound &s)
					  { return s.getStatus() == sf::Sound::Status::Stopped; });
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition({position.x, -position.y, ListenerZ});
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}
