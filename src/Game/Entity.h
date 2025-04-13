#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	sf::CircleShape Shape;

	float Size;

	sf::Vector2f GetPosition();

	void SetSize(float _siz);
	void SetOrigin(float _ox, float _oy);
	void SetPosition(float _px, float _py);
};

