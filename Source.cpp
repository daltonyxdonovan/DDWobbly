#pragma region ==INCLUDES==

// vvvv this line also requires the linker settings in project properties (linker>system) to be set to "windows subsystem" instead of "console subsystem" vvvv
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Button.h"
#include <iostream>
#include <fstream>

using namespace std;
#pragma endregion


#pragma region ==VARIABLES==


const int width{ 500 };
const int height{ 500 };

sf::Texture textureBuffer;
bool windowheld = false;
bool isDragging = false;
bool locked = false;
bool drawer = false;

int colorTicker = 0;
int colorBTicker = 10;
int ticker = 0;
int offset = 0; 

vector<sf::Color> colors;
sf::Color color;
sf::Color colorB;
sf::Vector2i dragStartPosition;
sf::Font font;
sf::Event event;
sf::Image icon;
sf::Sprite lockedSprite;
sf::Texture lockedIMG;
sf::Texture unlockedIMG;

sf::Text mod1; //bot1
sf::Text mod2; //bot2
sf::Text mod3; //bot3
sf::Text mod4; //bot4
sf::Text title;
sf::Text outputText1;
sf::Text outputText2;
sf::Text outputText3;
sf::Text outputText4;

sf::Text testText;

sf::RectangleShape titlebar1(sf::Vector2f(width - 60, 2));
sf::RectangleShape titlebar2(sf::Vector2f(width - 65, 2));
sf::RectangleShape titlebarTop(sf::Vector2f(width, 2));
sf::RectangleShape borderTop(sf::Vector2f(width, 2));
sf::RectangleShape borderBottom(sf::Vector2f(width, 2));
sf::RectangleShape borderLeft(sf::Vector2f(2, height));
sf::RectangleShape borderRight(sf::Vector2f(2, height));
sf::RectangleShape backer0(sf::Vector2f(width-80, 50));
sf::RectangleShape backer1(sf::Vector2f(width-80, 50));
sf::RectangleShape backer2(sf::Vector2f(width-80, 50));
sf::RectangleShape backer3(sf::Vector2f(width-80, 50));
sf::RectangleShape drawerBacker(sf::Vector2f(width,height));

sf::Vector2i mousePos = sf::Mouse::getPosition();

#pragma endregion

int main()
{

#pragma region ==VARIABLES INIT==

	srand(time(NULL));

	/*HWND hWnd = GetConsoleWindow();
	if (hWnd)
		ShowWindow(hWnd, SW_HIDE);*/

	//add colors to vector
	colors.push_back(sf::Color::White);
	colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Green);
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Yellow);
	colors.push_back(sf::Color::Magenta);
	colors.push_back(sf::Color::Cyan);
	colors.push_back(sf::Color(246,138,229));
	colors.push_back(sf::Color(98,164,222));
	colors.push_back(sf::Color(252,40,72));
	

	int colorChoice = rand()%colors.size();
	color = colors[colorChoice];
	colorTicker = colorChoice;
	colorB = sf::Color::Black;
	sf::RenderWindow window(sf::VideoMode(width, height), "DDWobbly", sf::Style::None);
	icon.loadFromFile("Icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	font.loadFromFile("resources/monospace.ttf");
	
	title.setFont(font);
	title.setString("DDWobbly");
	title.setCharacterSize(24);
	title.setFillColor(color);
	title.setStyle(sf::Text::Italic);
	title.setPosition(15, height-40);

	sf::Text lockedText;
	sf::Text tipText;
	lockedText.setFont(font);
	tipText.setFont(font);
	lockedText.setFillColor(color);
	tipText.setFillColor(color);
	lockedText.setString("LOCKED");
	tipText.setString("TIP: Use arrow keys to change color!");
	lockedText.setCharacterSize(50);
	tipText.setCharacterSize(20);
	lockedText.setPosition(sf::Vector2f(75, height + 150 + offset));
	tipText.setPosition(sf::Vector2f(75, height + 190 + offset));
	lockedText.setStyle(sf::Text::Bold);
	tipText.setStyle(sf::Text::Italic);


	lockedIMG.loadFromFile("resources/locked.png");
	
	lockedSprite.setPosition(width - 60, 11);
	
	unlockedIMG.loadFromFile("resources/unlocked.png");
	lockedSprite.setTexture(unlockedIMG);
	lockedSprite.setScale(sf::Vector2f(0.75f, 0.75f));

	mod1.setFont(font);
	mod1.setString("mod1");
	mod1.setCharacterSize(30);
	mod1.setFillColor(sf::Color::White);
	mod1.setPosition(50, 55);

	mod2.setFont(font);
	mod2.setString("mod2");
	mod2.setCharacterSize(30);
	mod2.setFillColor(sf::Color::White);
	mod2.setPosition(50, 155);

	mod3.setFont(font);
	mod3.setString("mod3");
	mod3.setCharacterSize(30);
	mod3.setFillColor(sf::Color::White);
	mod3.setPosition(50, 255);

	mod4.setFont(font);
	mod4.setString("mod4");
	mod4.setCharacterSize(30);
	mod4.setFillColor(sf::Color::White);
	mod4.setPosition(50, 355);

	Button exit(sf::Vector2f(width - 20, 20), sf::Vector2f(25, 25), sf::Color(0,0,0), sf::Color::White, "x", 24, true, false, false);
	Button mod1Button(sf::Vector2f(400,75),sf::Vector2f(100,30), sf::Color(0,0,0),sf::Color::Red,"OFFLINE",12,true, true, false);
	Button mod2Button(sf::Vector2f(400, 175), sf::Vector2f(100, 30), sf::Color(0, 0, 0), sf::Color::Red, "OFFLINE", 12, true, true, false);
	Button mod3Button(sf::Vector2f(400, 275), sf::Vector2f(100, 30), sf::Color(0, 0, 0), sf::Color::Red, "OFFLINE", 12, true, true, false);
	Button mod4Button(sf::Vector2f(400, 375), sf::Vector2f(100, 30), sf::Color(0, 0, 0), sf::Color::Red, "OFFLINE", 12, true, true, false);
	Button titleName(sf::Vector2f(220,height-23),sf::Vector2f(120,30),sf::Color::Black,sf::Color::White,"DDWOBBLY",24,true,false, true);

	titlebar1.setFillColor(color);
	titlebar2.setFillColor(color);
	titlebar1.setPosition(293, height - 27);
	titlebar2.setPosition(290, height - 22);
	titlebarTop.setFillColor(color);
	titlebarTop.setPosition(0, height-50);
	
	borderTop.setFillColor(color);
	borderBottom.setFillColor(color);
	borderLeft.setFillColor(color);
	borderRight.setFillColor(color);
	borderTop.setPosition(0, 0);
	borderBottom.setPosition(0, height - 2);
	borderLeft.setPosition(0, 0);
	borderRight.setPosition(width - 2, 0);

	backer0.setFillColor(sf::Color(20, 20, 20));
	backer1.setFillColor(sf::Color(20, 20, 20));
	backer2.setFillColor(sf::Color(20, 20, 20));
	backer3.setFillColor(sf::Color(20, 20, 20));

	backer0.setOutlineColor(color);
	backer1.setOutlineColor(color);
	backer2.setOutlineColor(color);
	backer3.setOutlineColor(color);

	backer0.setOutlineThickness(2);
	backer1.setOutlineThickness(2);
	backer2.setOutlineThickness(2);
	backer3.setOutlineThickness(2);

	backer0.setPosition(40, 50);
	backer1.setPosition(40, 150);
	backer2.setPosition(40, 250);
	backer3.setPosition(40, 350);

	outputText1.setFont(font);
	outputText1.setCharacterSize(12); // Adjust the size as neemod4Buttond
	outputText1.setFillColor(sf::Color::Green);
	outputText1.setPosition(50, 110); // Adjust the position as neemod4Buttond

	outputText2.setFont(font);
	outputText2.setCharacterSize(12); // Adjust the size as neemod4Buttond
	outputText2.setFillColor(sf::Color::Green);
	outputText2.setPosition(50, 210); // Adjust the position as neemod4Buttond

	outputText3.setFont(font);
	outputText3.setCharacterSize(12); // Adjust the size as neemod4Buttond
	outputText3.setFillColor(sf::Color::Green);
	outputText3.setPosition(50, 310); // Adjust the position as neemod4Buttond

	outputText4.setFont(font);
	outputText4.setCharacterSize(12); // Adjust the size as neemod4Buttond
	outputText4.setFillColor(sf::Color::Green);
	outputText4.setPosition(50, 410); // Adjust the position as neemod4Buttond

	drawerBacker.setFillColor(sf::Color(0,0,0));
	drawerBacker.setPosition(sf::Vector2f(0, height - 50+offset));



#pragma endregion
	



	while (window.isOpen())
	{
#pragma region ==VARS REFRESH==
		borderTop.setFillColor(color);
		borderBottom.setFillColor(color);
		borderLeft.setFillColor(color);
		borderRight.setFillColor(color);
		titlebar1.setFillColor(color);
		titlebar2.setFillColor(color);
		title.setFillColor(color);
		titlebarTop.setFillColor(color);
		backer0.setOutlineColor(color);
		backer1.setOutlineColor(color);
		backer2.setOutlineColor(color);
		backer3.setOutlineColor(color);
		exit.text_color = color;
		exit.outline_color = color;
		mod1Button.outline_color = color;
		mod2Button.outline_color = color;
		mod3Button.outline_color = color;
		mod4Button.outline_color = color;

		titleName.text_color = color;
		lockedSprite.setColor(color);

		titlebar1.setPosition(143, height - 27 + offset);
		titlebar2.setPosition(140, height - 22 + offset);
		titlebarTop.setPosition(0, height - 50 + offset);
		titleName.set_position(sf::Vector2f(75, height - 23 + offset));
		drawerBacker.setPosition(sf::Vector2f(0, height - 50 + offset));
		lockedText.setPosition(sf::Vector2f(width/2, height + 150 + offset));
		tipText.setPosition(sf::Vector2f(width/2, height + 230 + offset));
		lockedText.setOrigin(lockedText.getGlobalBounds().width/2,lockedText.getGlobalBounds().height/2);
		tipText.setOrigin(tipText.getGlobalBounds().width/2,tipText.getGlobalBounds().height/2);
		tipText.setFillColor(color);
		lockedText.setFillColor(color);


#pragma endregion

		if (drawer) //offset is the position of the drawer handle for the app drawer, not the window offset
		{
			if (offset > -450)
				offset -= 25;
		}
		else
		{
			if (offset < 0)
				offset += 25;
		}

		if (locked)
		{
			if (lockedSprite.getTexture() != &lockedIMG)
				lockedSprite.setTexture(lockedIMG);
			drawer = true;
			titleName.text_string = "UNLOCK";
		}
		else
		{
			if (lockedSprite.getTexture() != &unlockedIMG)
				lockedSprite.setTexture(unlockedIMG);
			drawer = false;
			titleName.text_string = "DDWOBBLY";
		}

		//if window is unfocused, lock it
		if (!window.hasFocus())
		{
			locked = true;
		}

		mousePos = sf::Mouse::getPosition(window);
		if (ticker > 0)
			ticker--;

#pragma region ==BUTTON CLICKS==
		if (exit.clicked && !locked && window.hasFocus())
		{
			window.close();
		}

		if (titleName.clicked && ticker == 0 && window.hasFocus())
		{
			ticker = 20;
			drawer = false;
			locked = false;
		}
#pragma endregion

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//check if mouse is within 50px of the top of the window
					if (mousePos.y < 50)
					{
						//check if mouse is within 50px of the right of the window
						if (mousePos.x > window.getSize().x - 70)
						{
							
						}
						else if (mousePos.x < 100) //this is here to disallow clicking in that area
						{

						}
						else
						{
							windowheld = true;

						}
					}

					//if lockedSprite is clicked, lock the window
					if (lockedSprite.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
						locked = !locked;
					}


				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					windowheld = false;
				}
			}
			//if arrow keys are pressed, change sf::Color color to the next sf::Color in vector of them
			if (event.type == sf::Event::KeyPressed)
			{
				

				if (event.key.code == sf::Keyboard::Right)
				{
					colorTicker++;
					if (colorTicker > colors.size() - 1)
						colorTicker = 0;
					color = colors[colorTicker];
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					colorTicker--;
					if (colorTicker < 0)
						colorTicker = colors.size() - 1;
					color = colors[colorTicker];
				}

				if (event.key.code == sf::Keyboard::Up && !locked)
				{
					//offset--;
				}
				if (event.key.code == sf::Keyboard::Down && !locked)
				{
					//offset++;
				}
			}
		}

		if (windowheld && !locked && !drawer) //offset to drag the window, but only unmod4Buttonr certain conditions
			window.setPosition(sf::Mouse::getPosition() - sf::Vector2i(window.getSize().x / 2, 25));

		




		window.clear(colorB);

#pragma region ==DRAW LOOP==
		window.draw(backer0);
		window.draw(backer1);
		window.draw(backer2);
		window.draw(backer3);

		window.draw(mod1);
		window.draw(mod2);
		window.draw(mod3);
		window.draw(mod4);
		
		mod1Button.update(window);
		mod1Button.draw(window);
		mod2Button.update(window);
		mod2Button.draw(window);
		mod3Button.update(window);
		mod3Button.draw(window);
		mod4Button.update(window);
		mod4Button.draw(window);

		exit.update(window);
		exit.draw(window);
		window.draw(lockedSprite);

		window.draw(outputText1);
		window.draw(outputText2);
		window.draw(outputText3);
		window.draw(outputText4);

		window.draw(drawerBacker);
		titleName.draw(window);
		titleName.update(window);
		window.draw(titlebar1);
		window.draw(titlebar2);
		window.draw(titlebarTop);

		window.draw(tipText);
		window.draw(lockedText);

		window.draw(borderTop);
		window.draw(borderBottom);
		window.draw(borderLeft);
		window.draw(borderRight);
#pragma endregion


		window.setFramerateLimit(60);
		window.display();
	}
    return 0;
}