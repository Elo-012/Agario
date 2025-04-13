#include "pch.h"
#include "Food.h"

Food::Food()
{
	SetSize(std::rand() % 9 + 1);
	
	SetOrigin(Size, Size);
	float posX = std::rand() % 10000 - 5000;
	float posY = std::rand() % 10000 - 5000;
	SetPosition(posX, posY);

	std::vector<sf::Color> couleurs = {
		sf::Color::Blue,
		sf::Color::Cyan,
		sf::Color::Yellow,
		sf::Color(255, 105, 180), // rose
		sf::Color(138, 43, 226),  // violet
		sf::Color(255, 165, 0),   // orange
		sf::Color(0, 255, 255),   // turquoise flashy
		sf::Color(255, 20, 147),  // deep pink
		sf::Color(75, 0, 130)     // indigo
	};

	int index = std::rand() % couleurs.size();
	Shape.setFillColor(couleurs[index]);
}

Food::~Food()
{
}
