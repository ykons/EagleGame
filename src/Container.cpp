#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <Container.hpp>

namespace GUI
{

	Container::Container()
		: mChildren(), mSelectedChild(-1)
	{
	}

	void Container::pack(Component::Ptr component)
	{
		mChildren.push_back(component);

		if (!hasSelection() && component->isSelectable())
			select(mChildren.size() - 1);
	}

	bool Container::isSelectable() const
	{
		return false;
	}

	void Container::handleEvent(const sf::Event &event)
	{
		// If we have selected a child then give it events
		if (hasSelection() && mChildren[mSelectedChild]->isActive())
		{
			mChildren[mSelectedChild]->handleEvent(event);
		}
		else if (event.is<sf::Event::KeyReleased>())
		{
			if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::W || event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Up)
			{
				selectPrevious();
			}
			else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::S || event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Down)
			{
				selectNext();
			}
			else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Enter || event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Space)
			{
				if (hasSelection())
					mChildren[mSelectedChild]->activate();
			}
		}
	}

	void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for (const Component::Ptr &child : mChildren)
			target.draw(*child, states);
	}

	bool Container::hasSelection() const
	{
		return mSelectedChild >= 0;
	}

	void Container::select(std::size_t index)
	{
		if (mChildren[index]->isSelectable())
		{
			if (hasSelection())
				mChildren[mSelectedChild]->deselect();

			mChildren[index]->select();
			mSelectedChild = index;
		}
	}

	void Container::selectNext()
	{
		if (!hasSelection())
			return;

		// Search next component that is selectable, wrap around if necessary
		int next = mSelectedChild;
		do
			next = (next + 1) % mChildren.size();
		while (!mChildren[next]->isSelectable());

		// Select that component
		select(next);
	}

	void Container::selectPrevious()
	{
		if (!hasSelection())
			return;

		// Search previous component that is selectable, wrap around if necessary
		int prev = mSelectedChild;
		do
			prev = (prev + mChildren.size() - 1) % mChildren.size();
		while (!mChildren[prev]->isSelectable());

		// Select that component
		select(prev);
	}

}
