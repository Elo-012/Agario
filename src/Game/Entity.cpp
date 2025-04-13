#include "pch.h"
#include "Entity.h"

sf::Vector2f Entity::GetPosition()
{
	return sf::Vector2f(Shape.getPosition());
}

void Entity::SetSize(float _siz)
{
	Size = _siz;
	Shape.setRadius(Size);
}

void Entity::SetOrigin(float _ox, float _oy)
{
	Shape.setOrigin(_ox, _oy);
}

void Entity::SetPosition(float _px, float _py)
{
	Shape.setPosition(_px, _py);
}
