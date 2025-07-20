#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace sf
{
    class Event;
}

namespace GUI
{

    class Component : public sf::Drawable, public sf::Transformable
    {
    public:
        typedef std::shared_ptr<Component> Ptr;

    public:
        Component();
        virtual ~Component();

        virtual bool isSelectable() const = 0;
        bool isSelected() const;
        virtual void select();
        virtual void deselect();

        virtual bool isActive() const;
        virtual void activate();
        virtual void deactivate();

        virtual void handleEvent(const sf::Event &event) = 0;

    private:
        bool mIsSelected;
        bool mIsActive;
    };

}

#endif // COMPONENT_HPP
