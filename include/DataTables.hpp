#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>

#include <ResourceIdentifiers.hpp>

class Aircraft;

struct Direction
{
	Direction(float angle, float distance)
		: angle(angle), distance(distance)
	{
	}

	float angle;
	float distance;
};

struct AircraftData
{
	int hitpoints;
	float speed;
	Textures::ID texture;
	sf::IntRect textureRect;
	sf::Time fireInterval;
	std::vector<Direction> directions;
	bool hasRollAnimation;
};

struct ProjectileData
{
	int damage;
	float speed;
	Textures::ID texture;
	sf::IntRect textureRect;
};

struct PickupData
{
	std::function<void(Aircraft &)> action;
	Textures::ID texture;
	sf::IntRect textureRect;
};

struct ParticleData
{
	sf::Color color;
	sf::Time lifetime;
};

std::vector<AircraftData> initializeAircraftData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData> initializePickupData();
std::vector<ParticleData> initializeParticleData();

#endif // DATATABLES_HPP
