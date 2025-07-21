#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

namespace sf
{
    class Texture;
    class Font;
}

namespace Textures
{
    enum ID
    {
        Eagle,
        Raptor,
        Avenger,
        Bullet,
        Missile,
        Desert,
        HealthRefill,
        MissileRefill,
        FireSpread,
        FireRate,
        TitleScreen,
        ButtonNormal,
        ButtonSelected,
        ButtonPressed
    };
}

namespace Fonts
{
    enum ID
    {
        Main
    };
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif // RESOURCEIDENTIFIERS_HPP
