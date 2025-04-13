#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	const char* Username;

	float speed;
	
	float defaultsize = 30;

	void SetName(const char* _name);
	void SetSpeed(float _spd);

	void Update(float deltaTime);

	bool CheckCollision(const sf::CircleShape& food);
};

