#include "pch.h"
#include "Player.h"
#include "Food.h"

#define WINDOWWITH 800
#define WINDOWHEIGHT 600


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

	sf::Event event;
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		std::cout << player.Size << std::endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float zoomFactor = player.Size / 50.f;
		Camera.setSize(WINDOWWITH * zoomFactor, WINDOWHEIGHT * zoomFactor);
		Camera.setCenter(player.GetPosition());
		Nouriture.erase(
			std::remove_if(Nouriture.begin(), Nouriture.end(),
				[&](Food& M) {
					if (player.CheckCollision(M.Shape)) {
						float gain = M.Size / (player.Size * 0.05f + 1.f); // Plus t'es gros, moins tu gagnes
						player.SetSize(player.Size + gain);
						return true; // On le retire du vector
					}
					return false;
				}),
			Nouriture.end()
		);

		player.Update(deltaTime);
		window.clear();
		for (auto& M : Nouriture)
		{
			window.draw(M.Shape);
		}
		window.draw(player.Shape);
		window.setView(Camera);
		window.display();
	}

	return 0;
}