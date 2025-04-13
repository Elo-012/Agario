#include "pch.h"
#include "Player.h"
#include "Food.h"
#include "OnLineSystem.h"

#define WINDOWWITH 800
#define WINDOWHEIGHT 600

sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t) {
	return a + (b - a) * t;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOWWITH, WINDOWHEIGHT), "Agar IO");
	sf::Clock clock;

	Player player;
	player.SetSpeed(150);
	player.SetPosition(100, 100);

	std::vector<Food> Nouriture;
	for (int i = 0; i < 5000; i++)
	{
		Food I;
		Nouriture.push_back(I);
	}

	sf::View Camera;
	Camera.setSize(WINDOWWITH, WINDOWHEIGHT); // Taille de la vue
	sf::Vector2f cameraPos = player.GetPosition(); // position initiale
	sf::Vector2f currentViewSize(WINDOWWITH, WINDOWHEIGHT); // taille actuelle de la vue

	sf::Event event;
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		player.Update(deltaTime);

		// Cible de la caméra
		sf::Vector2f targetCam = player.GetPosition();
		cameraPos = Lerp(cameraPos, targetCam, 5.f * deltaTime); // caméra fluide

		// Cible du zoom
		float zoomFactor = player.Size / 50.f;
		sf::Vector2f targetViewSize(WINDOWWITH * zoomFactor, WINDOWHEIGHT * zoomFactor);

		// Lerp pour dézoom fluide
		currentViewSize = Lerp(currentViewSize, targetViewSize, 1.f * deltaTime); // <-- plus petit = plus lent

		Camera.setSize(currentViewSize);
		Camera.setCenter(cameraPos);
		window.setView(Camera);

		// Manger
		Nouriture.erase(
			std::remove_if(Nouriture.begin(), Nouriture.end(),
				[&](Food& M) {
					if (player.CheckCollision(M.Shape)) {
						float gain = M.Size / (player.Size * 0.05f + 1.f);
						player.SetSize(player.Size + gain);
						return true;
					}
					return false;
				}),
			Nouriture.end()
		);

		window.clear();
		for (auto& M : Nouriture)
		{
			window.draw(M.Shape);
		}
		window.draw(player.Shape);
		window.display();
	}

	return 0;
}