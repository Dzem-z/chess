#include <vector>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "chess.h"
#include "chess.cpp"
#include "math.h"

void show(sf::VertexArray*, int, int, bool);
void MoveSprite(int, int, sf::Sprite **);


int s = 640;
int cir_a = 16;	// circle accuracy: number of vertices of geometric circle shape

int main(int argc, char ** argv) {

	sf::RenderWindow window(sf::VideoMode(s, s), "chess", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//preinitialization

	sf::VertexArray chessfields(sf::Quads, 256);					// chessfield rectangle sprites array
	sf::VertexArray circles[64];									// cirle sprites array
													
	//sf::RenderWindow win1;

	sf::Vector2f mouse_position;									// vector for keeping mouse position
	
	for (int i = 0; i < 64; i++)									// circles initialization
	{
		circles[i] = sf::VertexArray(sf::TriangleFan, cir_a);
		for (int j = 0; j < cir_a; j++)
		{
			circles[i][j].position = sf::Vector2f(s/16.f + s / 32.f * sin(2 * 3.14 * j / cir_a),s/16.f + s / 32.f * cos(2 * 3.14 * j / cir_a))+sf::Vector2f(s/8.f*(i%8),s/8.f*(i/8));
			circles[i][j].color = sf::Color(0,0,0,0);
		}

	}


	for (int a = 0; a < 4; a++) {					//chessfields initialization
		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				chessfields[a * 64 + i * 8 + j].color = sf::Color(153, 204, 255);
			for (int j = 0; j < 4; j++)
				chessfields[a * 64 + i * 8 + j+4].color = sf::Color(0, 38, 77);
				
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				chessfields[a*64+32 + i * 8 + j].color = sf::Color(0, 38, 77);
			for (int j = 0; j < 4; j++)
				chessfields[a*64+32 + i * 8 + j + 4].color = sf::Color(153, 204, 255);
		}
	}
	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++) {
			chessfields[a * 32 + b*4].position = sf::Vector2f(s / 8.f * b, s / 8.f * a);
			chessfields[a * 32 + b*4+1].position = sf::Vector2f(s / 8.f * (b+1), s / 8.f * a);
			chessfields[a * 32 + b * 4 + 2].position = sf::Vector2f(s / 8.f * (b + 1), s / 8.f * (a+1));
			chessfields[a * 32 + b * 4 + 3].position = sf::Vector2f(s / 8.f * b, s / 8.f * (a+1));
		}
	}
	//textures
	std::string name = "figure";
	sf::Texture texture[12];
	for (int i = 0; i < 12; i++)
	{
		if (!texture[i].loadFromFile((name+std::to_string(i)+"l.png").c_str()))
		{
			throw("texture error");
		}
	}
	sf::Sprite promotion_sprites[4];
	for (int i = 0; i < 4; i++)
		promotion_sprites[i].setPosition(i * 80, 0);
	sf::Sprite* sprites = new sf::Sprite[32];
	sprites[0].setTexture(texture[0]), sprites[1].setTexture(texture[1]), sprites[2].setTexture(texture[2]), sprites[3].setTexture(texture[3]), sprites[4].setTexture(texture[4]),
		sprites[5].setTexture(texture[2]), sprites[6].setTexture(texture[1]), sprites[7].setTexture(texture[0]), sprites[24].setTexture(texture[5]), sprites[25].setTexture(texture[6]),
		sprites[26].setTexture(texture[7]), sprites[27].setTexture(texture[8]), sprites[28].setTexture(texture[9]), sprites[29].setTexture(texture[7]), sprites[30].setTexture(texture[6]);
	sprites[31].setTexture(texture[5]);
	
	for (int i = 8; i < 16; i++)
		sprites[i].setTexture(texture[10]);
	for (int i = 16; i < 24; i++)
		sprites[i].setTexture(texture[11]);
	for (int i = 0; i < 16; i++)
	{	
		sprites[ i ].setColor(sf::Color(sprites[ i ].getColor().r, sprites[ i ].getColor().g, sprites[ i ].getColor().b, 0));
		sprites[i].setPosition(sf::Vector2f(s/8 * (i % 8), s/8 * (i / 8)));
	}
	for (int i = 16; i < 32; i++){
		sprites[i].setPosition(sf::Vector2f(s/8 * (i % 8), s/8 * ((i-16)/8) + 3.f/4*s));
		sprites[ i ].setColor(sf::Color(sprites[ i ].getColor().r, sprites[ i ].getColor().g, sprites[ i ].getColor().b, 0));
	}
	sf::Sprite* Spr[64];
	for (int i = 16; i < 48; i++)
		Spr[i] = nullptr;
	for (int i = 0; i < 16; i++)
		Spr[i] = &sprites[i];
	for (int i = 16; i < 32; i++)
		Spr[32 + i] = &sprites[i];


	//engine

	humanPlayer white = humanPlayer(circles);
	humanPlayer black = humanPlayer(circles);
	chessGame game = chessGame(&white, &black, true, true, Spr);
	
	//end
	
	game.start();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				mouse_position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				if (mouse_position.x < s && mouse_position.x > 0 && mouse_position.y < s && mouse_position.y > 0)
					game.fieldClicked(mouse_position);
			}
		}
		
		
		game.move();



		window.clear(sf::Color::White);
		window.draw(chessfields);
		for (int i = 0; i < 64; i++)
			window.draw(circles[i]);
		for (int i = 0; i < 64; i++)
		{
			if(Spr[i] != nullptr)
				window.draw(*Spr[i]);
		}
		window.display();
	}
	delete[] sprites;
	return 0;
}

void MoveSprite(
				int from,				// position from which sprite is being moved
 				int to, 				// position to which sprite is being moved
				sf::Sprite** Spr		// array of sprites
				)
{
	Spr[to] = Spr[from];
	Spr[from] = nullptr;
	Spr[to]->setPosition(s/8 * (to % 8), s/8 * (to / 8));
}

void ShowCircles(
				sf::VertexArray * circle,	// pointer to Vertex Array containing circle sprites
				int cir_a, 				// number of vertices of the circle shape
				bool f					// flag used to hiding and showing the circle: 1 for showing, 0 for hiding
				) {
	for (int i = 0; i < cir_a; i++)
		(*circle)[ i ].color = sf::Color(0, 0, 0, f ? 255 : 0);
}

void ShowSprite(
				sf::Sprite * spr,		//pointer to sprite 
				bool f					// flag used to hiding and showing the sprite: 1 for showing, 0 for hiding
				){
		spr->setColor(sf::Color(spr->getColor().r, spr->getColor().g, spr->getColor().b, f ? 255 : 0));			
}

void HideAllCircles(
					sf::VertexArray * c,	// Vertex Array containing circle sprites
					int cir_a			// number of vertices of the circle shape
					){
	for(int pos = 0; pos < 64; pos++)
		ShowCircles(&c[ pos ], cir_a, 0);
}

