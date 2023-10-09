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
#define WIN32_LEAN_AND_MEAN
#include <filesystem>
#include <Windows.h>
#include <ShlObj.h>

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

std::vector<sf::Color> colors;
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

sf::Text dirText;

#pragma endregion

void InstallBepinex(const std::string& dir) {
    std::cout << "Installing Bepinex to the directory specified at launch!" << std::endl;
    std::string command = "Expand-Archive -Path .\\resources\\bepinex.zip -DestinationPath " + dir;
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Bepinex has been successfully installed to " << dir << "!" << std::endl;
    } else {
        std::cout << "Failed to install Bepinex. sadge. Please head to https://discord.gg/daMWV3TTea and let @Daltonyx know, with either a screenshot or a copy of this terminal's output to help others in the future not encounter this problem!" << std::endl;
    }
}

bool CheckForBepinex(const std::string& dir) {
    std::string fullPath = dir + "\\BepInEx"; // Construct the full path to the 'BepInEx' folder
	LPCWSTR fullPathW;
	fullPathW = (LPCWSTR)fullPath.c_str();

    // Use the Windows API function GetFileAttributes to check if the folder exists
    DWORD fileAttributes = GetFileAttributes(fullPathW);

    if (fileAttributes != INVALID_FILE_ATTRIBUTES && (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        // 'BepInEx' folder exists in the specified directory
		std::cout << "User has BepInEx installed. Continuing!" << std::endl;
        return true;
    } else {
        // 'BepInEx' folder does not exist in the specified directory
		std::cout << "User does not have BepInEx installed. Attempting install..." << std::endl;
        return false;
    }
}


void InstallMod1(std::string dir, int& ticker)
{
	std::cout << "Installing Mod 1..." << std::endl;

	if (CheckForBepinex(dir))
	{
		
	}
	else
	{
		InstallBepinex(dir);
	}

	if (std::filesystem::exists(dir + "\\BepInEx\\plugins\\WobblyLife_ConsoleCommands.dll"))
	{
		std::cout << "Console Commands already installed. Skipping..." << std::endl;
		ticker = 120;
		return;
	}

	//copy resources/WobblyLife_ConsoleCommands.dll to dir/BepInEx/plugins
	std::ifstream src("resources/WobblyLife_ConsoleCommands.dll", std::ios::binary);
	std::ofstream dst(dir + "\\BepInEx\\plugins\\WobblyLife_ConsoleCommands.dll", std::ios::binary);
	dst << src.rdbuf();



	ticker = 120; 
}

void InstallMod2(std::string dir, int& ticker)
{
	std::cout << "Installing Mod 2..." << std::endl;

	if (CheckForBepinex(dir))
	{
		
	}
	else
	{
		InstallBepinex(dir);
	}

	if (std::filesystem::exists(dir + "\\BepInEx\\plugins\\WobblyLife_SizeModifier.dll"))
	{
		std::cout << "WobblyLife_SizeModifier already installed. Skipping..." << std::endl;
		ticker = 120;
		return;
	}

	//copy resources/WobblyLife_ConsoleCommands.dll to dir/BepInEx/plugins
	std::ifstream src("resources/WobblyLife_SizeModifier.dll", std::ios::binary);
	std::ofstream dst(dir + "\\BepInEx\\plugins\\WobblyLife_SizeModifier.dll", std::ios::binary);
	dst << src.rdbuf();

	ticker = 120; 
}

void InstallMod3(const std::string& dir, int& ticker) {
    std::cout << "Installing Mod 3..." << std::endl;

    // Construct the source and destination paths
    std::string sourcePath = "resources\\Game.dll";
    std::string destinationPath = dir + "\\Wobbly Life_Data\\Managed\\Game.dll";
	LPCWSTR destinationPathW;
	destinationPathW = (LPCWSTR)destinationPath.c_str();
	LPCWSTR sourcePathW;
	sourcePathW = (LPCWSTR)sourcePath.c_str();

    // Use the Windows API function CopyFile to replace the file
    if (CopyFile(sourcePathW, destinationPathW, FALSE)) {
        std::cout << "Mod 3 has been successfully installed.\n\nWARNING: THIS REPLACES GAME.DLL IN YOUR GAME WITH ONE I'VE MODDED. IF YOU EXPERIENCE ANY WONKY BEHAVIOUR, PLEASE REPORT IT TO @DALTONYX IN THE DISCORD SERVER, AND IF IT IS UNDESIRABLE BEHAVIOUR GO VERIFY CACHE ON STEAM TO REPLACE IT WITH THE DEFAULT GAME.DLL FOR THE GAME. THIS WILL FIX IT" << std::endl;
    } else {
        std::cerr << "Failed to replace your game's DLL.\nIs Wobbly Life open while you're doing this? Naughty naughty." << std::endl;
    }

    // Set the ticker value to 120
    ticker = 120;
}

void InstallMod4(std::string dir, int& ticker)
{
	std::cout << "Installing Mod 4..." << std::endl;

	ticker = 120; 
}


int main()
{
	sf::Text install1;
	sf::Text install2;
	sf::Text install3;
	sf::Text install4;

	install1.setString("Finished!");
	install2.setString("Finished!");
	install3.setString("Finished!");
	install4.setString("Finished!");

	install1.setFont(font);
	install2.setFont(font);
	install3.setFont(font);
	install4.setFont(font);

	install1.setStyle(sf::Text::Bold);
	install2.setStyle(sf::Text::Bold);
	install3.setStyle(sf::Text::Bold);
	install4.setStyle(sf::Text::Bold);

	install1.setCharacterSize(12);
	install2.setCharacterSize(12);
	install3.setCharacterSize(12);
	install4.setCharacterSize(12);

	install1.setFillColor(sf::Color::Green);
	install2.setFillColor(sf::Color::Green);
	install3.setFillColor(sf::Color::Green);
	install4.setFillColor(sf::Color::Green);

	int install1Ticker = 0;
	int install2Ticker = 0;
	int install3Ticker = 0;
	int install4Ticker = 0;

	std::string folderPath = "You didn't select a folder, I won't work now.";

	char buffer[MAX_PATH];
	BROWSEINFOA info = { 0 };
	info.hwndOwner = NULL;
	info.pidlRoot = NULL;
	info.pszDisplayName = buffer;
	info.lpszTitle = "SELECT YOUR WOBBLY LIFE FOLDER\nDEFAULT IS NORMALLY: \nTHIS PC->C://PROGRAM FILES(x86)/STEAM/STEAMAPPS/COMMON/WOBBLY LIFE";
	info.ulFlags = BIF_USENEWUI;

	LPITEMIDLIST item = SHBrowseForFolderA(&info);

	if (item != NULL) {
		SHGetPathFromIDListA(item, buffer);
		folderPath = buffer;
		dirText.setFillColor(sf::Color::White);
		CoTaskMemFree(item);
		dirText.setCharacterSize(10);
	}
	else
	{
		dirText.setFillColor(sf::Color::Red);
		dirText.setCharacterSize(15);
	}

	dirText.setString(folderPath);
	dirText.setFont(font);
	
	dirText.setStyle(sf::Text::Bold);
	dirText.setPosition(sf::Vector2f(width/2, height-70));
	


#pragma region ==VARIABLES INIT==



	srand(time(NULL));

	/*HWND hWnd = GetConsoleWindow();
	if (hWnd)
		ShowWindow(hWnd, SW_HIDE);*/

	//add colors to vector
	colors.push_back(sf::Color::White);
	/*colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Green);
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Yellow);
	colors.push_back(sf::Color::Magenta);
	colors.push_back(sf::Color::Cyan);
	colors.push_back(sf::Color(246,138,229));
	colors.push_back(sf::Color(98,164,222));
	colors.push_back(sf::Color(252,40,72));*/
	

	int colorChoice = rand()%colors.size();
	color = colors[colorChoice];
	//dirText.setFillColor(color);
	dirText.setOrigin(dirText.getLocalBounds().width / 2, dirText.getLocalBounds().height / 2);
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
	mod1.setString("Console Commands");
	mod1.setCharacterSize(15);
	mod1.setFillColor(sf::Color::White);
	mod1.setPosition(50, 65);

	mod2.setFont(font);
	mod2.setString("Size Modifier");
	mod2.setCharacterSize(15);
	mod2.setFillColor(sf::Color::White);
	mod2.setPosition(50, 165);

	mod3.setFont(font);
	mod3.setString("All Artifacts/Free Cars/\nFree Pets/Free Clothes");
	mod3.setCharacterSize(15);
	mod3.setFillColor(sf::Color::White);
	mod3.setPosition(50, 255);

	mod4.setFont(font);
	mod4.setString("    ==NOT MADE YET==\nSuggest mods on Discord!");
	mod4.setCharacterSize(15);
	mod4.setFillColor(sf::Color::Red);
	mod4.setPosition(70, 355);

	Button exit(sf::Vector2f(width - 20, 20), sf::Vector2f(25, 25), sf::Color(0,0,0), sf::Color::White, "x", 24, true, false, false);
	Button mod1Button(sf::Vector2f(400,75),sf::Vector2f(100,30), sf::Color(0,0,0),sf::Color::White,"INSTALL",12,true, true, false);
	install1.setPosition(sf::Vector2f(width/2, 108));
	Button mod2Button(sf::Vector2f(400, 175), sf::Vector2f(100, 30), sf::Color(0, 0, 0), sf::Color::White, "INSTALL", 12, true, true, false);
	install2.setPosition(sf::Vector2f(width / 2, 208));
	Button mod3Button(sf::Vector2f(400, 275), sf::Vector2f(100, 30), sf::Color(0, 0, 0), sf::Color::White, "INSTALL", 12, true, true, false);
	install3.setPosition(sf::Vector2f(width / 2, 308));
	Button mod4Button(sf::Vector2f(400, 375), sf::Vector2f(100, 30), sf::Color(0, 0, 0), sf::Color::White, "INSTALL", 12, true, true, false);
	install4.setPosition(sf::Vector2f(width / 2, 408));
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
		if (install1Ticker >0)
			install1Ticker--;
		if (install2Ticker >0)
			install2Ticker--;
		if (install3Ticker >0)
			install3Ticker--;
		if (install4Ticker >0)
			install4Ticker--;

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
		dirText.setOrigin(dirText.getLocalBounds().width / 2, dirText.getLocalBounds().height / 2);
		//dirText.setFillColor(color);

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

		if (mod1Button.clicked)
		{
			InstallMod1(folderPath, install1Ticker);
		}

		if (mod2Button.clicked)
		{
			InstallMod2(folderPath, install2Ticker);
		}

		if (mod3Button.clicked)
		{
			InstallMod3(folderPath, install3Ticker);
		}

		if (mod4Button.clicked)
		{
			InstallMod4(folderPath, install4Ticker);
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
						else if (locked && mousePos.x < 150) //this is here to disallow clicking in that area
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

		install1.setOrigin(install1.getLocalBounds().width / 2, install1.getLocalBounds().height / 2);
		install2.setOrigin(install2.getLocalBounds().width / 2, install2.getLocalBounds().height / 2);
		install3.setOrigin(install3.getLocalBounds().width / 2, install3.getLocalBounds().height / 2);
		install4.setOrigin(install4.getLocalBounds().width / 2, install4.getLocalBounds().height / 2);
		
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



		window.draw(dirText);

		if (install1Ticker > 0)
			window.draw(install1);
		if (install2Ticker > 0)
			window.draw(install2);
		if (install3Ticker >0)
			window.draw(install3);
		if (install4Ticker > 0)
			window.draw(install4);

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
