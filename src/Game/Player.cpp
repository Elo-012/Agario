#include "pch.h"
#include "Player.h"

Player::Player()
{
	Shape.setRadius(defaultsize);
	Shape.setOrigin(defaultsize, defaultsize);
	Shape.setFillColor(sf::Color::Green);
	Size = defaultsize;
}

Player::~Player()
{
}

void Player::SetName(const char* _name)
{
	Username = _name;
}

void Player::SetSpeed(float _spd)
{
	speed = _spd;
}

void Player::Update(float deltaTime)
{
	SetSize(Size);
	SetOrigin(Size, Size);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		Shape.move(-speed * deltaTime, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Shape.move(speed * deltaTime, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		Shape.move(0.0f, -speed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Shape.move(0.0f, speed * deltaTime);
	}
}

bool Player::CheckCollision(const sf::CircleShape& food)
{
	// Calculer la distance entre le centre du joueur et celui de la nourriture
	float distance = std::sqrt(
		std::pow(Shape.getPosition().x - food.getPosition().x, 2) +
		std::pow(Shape.getPosition().y - food.getPosition().y, 2)
	);

	// Vérifier si la distance est inférieure à la somme des rayons
	return distance < (Shape.getRadius() + food.getRadius());
}

