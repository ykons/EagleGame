#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

#include <StateIdentifiers.hpp>
#include <ResourceIdentifiers.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

namespace sf
{
	class RenderWindow;
}

class StateStack;
class Player;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow &window, TextureHolder &textures, FontHolder &fonts, Player &player,
				MusicPlayer &music, SoundPlayer &sounds);

		sf::RenderWindow *window;
		TextureHolder *textures;
		FontHolder *fonts;
		Player *player;
		MusicPlayer *music;
		SoundPlayer *sounds;
	};

public:
	State(StateStack &stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event &event) = 0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

private:
	StateStack *mStack;
	Context mContext;
};

#endif // STATE_HPP
