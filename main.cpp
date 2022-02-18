#include "NBody.hpp"

int main(int argc, char* argv[]) 
{
	int r_count;		//radius of universe
	double radius;

	double time = std::atof(argv[1]), delta_T = std::atof(argv[2]);		//time 

	//set the program's fundamentals, background, audio, fonts
	sf::Font font;
	if (!font.loadFromFile("fFont.ttf")) 
	{
		std::cout << "Couldn't load font!" << std::endl;
		exit(EXIT_FAILURE);
	}
	vars newV = setEnv(font);
	
	/*
	sf::Music music;		//set background music
	if (!music.openFromFile("2001.wav"))
		std::cout << "Couldn't play music!" << std::endl;
	music.setLoop(true);
	music.play();
	*/

	sf::Texture tex;
	tex.loadFromImage(newV._backg);
	sf::Sprite background;
	background.setTexture(tex);
	
	sf::Vector2u pSize;
	pSize = tex.getSize();

	std::cin >> r_count >> radius;

	double x, y, v_x, v_y, m, v_time = 0.0;
	std::string name;
	sf::Vector2f position, velocity, frc;
	std::vector<Body*> vBody;

	for (int i = 1; i <= r_count; i++) 
	{
		std::cin >> x >> y >> v_x >> v_y >> m >> name;
		position.x = x;
		position.y = y;
		velocity.x = v_x;
		velocity.y = v_y;

		Body* newBody = new (std::nothrow) Body(position, velocity, m, name);
		newBody->detPos(radius, pSize);
		vBody.push_back(newBody);
	}
	
	sf::Text timer;
	timer.setFont(font);

	timer.setPosition(0.f, 0.f);
	timer.setScale(.5f, .5f);
	
	sf::RenderWindow window(sf::VideoMode(pSize.x, pSize.y), "ps3a");
	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				std::cout << r_count << std::endl;
				std::cout << radius << std::endl;
				printVariables(vBody);
				window.close();
			}
		}
		
		window.clear(sf::Color::Black);
		window.draw(background);

		//draw bodies at every time step
		if (v_time<time) 
		{
			for (std::vector<Body*>::iterator it1 = vBody.begin(); it1 != vBody.end(); ++it1) 
			{
				sf::Vector2f force;
				for (std::vector<Body*>::iterator it2 = vBody.begin(); it2 != vBody.end(); ++it2) 
				{
					if ((*it1)->getName() != (*it2)->getName()) 
					{
						frc = pForce((*it1), (*it2));
						force.x += frc.x;
						force.y += frc.y;
					}
				}
				
				(*it1)->setfNet(force);

			}
			
			for (std::vector<Body*>::iterator it = vBody.begin(); it != vBody.end(); ++it) 
			{
				step(delta_T, radius, pSize, (*it));
				window.draw((*it)->getSprite());
				sf::sleep(sf::seconds(.005));
			}
			
			timer.setString(std::to_string(v_time));
			newV._timeStamp.setString(std::to_string(v_time));
			v_time += (delta_T);
		}
		
		window.draw(timer);
		
		window.display();
	}
	
	return EXIT_SUCCESS;
}
