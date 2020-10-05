#include "Level1State.h"


Level1State::Level1State(GameStateManager & gsm): gsm(gsm), tileMap(30), background("Resources/Backgrounds/grassbg1.gif", 0.5) 
{
	//Init();
}

void Level1State::Update(sf::RenderWindow * window, float frametime) 
{
	// Portals
	for (int i = 0; i < portals.size(); i++)
	{
		portals[i]->Update(frametime);

		if (player->intersects(*portals[i]))
		{
			
			if (portals.size() > 1)
			{
				player->setPosition(portals[i + 1]->getX(), portals[i + 1]->getY());

				delete portals[i + 1];
				portals.erase(portals.begin() + (i + 1));
			}
				
			delete portals[i];

			portals.erase(portals.begin() + i);
			i--;

		}

	}

	// Health Pickups
	for (int i = 0; i < heartPickups.size(); i++)
	{
		if (player->intersects(*heartPickups[i]))
		{
			player->increaseHealth(10);

			delete heartPickups[i];

			heartPickups.erase(heartPickups.begin() + i);
			i--;
		}
	}

	// Purple Bad Health Pickups
	for (int i = 0; i < pHeartPickups.size(); i++)
	{
		if (player->intersects(*pHeartPickups[i]))
		{
			player->decreaseHealth(10);

			delete pHeartPickups[i];

			pHeartPickups.erase(pHeartPickups.begin() + i);
			i--;
		}
	}

	// Fire Pickups
	for (int i = 0; i < firePickups.size(); i++)
	{
		if (player->intersects(*firePickups[i]))
		{
			player->increaseFire(10);

			delete firePickups[i];

			firePickups.erase(firePickups.begin() + i);
			i--;
		}
	}
		
	 //Use this to find the x-y coords
	 // of position in the level x = 1785 (2280,491)
	/*int x = player->getX();
	int y = player->getY();*/
		
	player->Update(frametime);

	/* Displaying player health in HUD */
	health = player->getHealth();
	std::stringstream ss;
	ss << health;
	std::string phealth = ss.str();
	playerHealth.setFont(font);
	playerHealth.setString("Health: " + phealth + "%");
	playerHealth.setPosition(5, 5);
	playerHealth.setColor(sf::Color(255, 255, 255));

	/* Displaying player score in HUD */
	score = player->getScore();
	std::stringstream sScore;
	sScore << score;
	std::string pScore = sScore.str();
	playerScore.setFont(font);
	playerScore.setString("Score: " + pScore);
	playerScore.setPosition(5, 35);
	playerScore.setColor(sf::Color(255, 255, 255));

	/* Displaying player Fire left in HUD */
	fireLeft = player->getFire();
	maxFires = player->getMaxFire();
	std::stringstream sFire;
	std::stringstream sMaxFire;
	sFire << fireLeft;
	sMaxFire << maxFires;
	std::string playerFireLeft = sFire.str();
	std::string playerMaxFire = sMaxFire.str();
	playerFire.setFont(font);
	playerFire.setString("Fire: " + playerFireLeft + " / " + playerMaxFire);
	playerFire.setPosition(5, 65);
	playerFire.setColor(sf::Color(255, 255, 255));


	tileMap.setPosition(((WINWIDTH*WINSCALE) / 2 - player->getX()) , ((WINHEIGHT*WINSCALE) / 2 - player->getY()));
	background.setPosition(tileMap.getX(), tileMap.getY());

	//attack enemies
	player->checkAttack(enemies);
	
	//update all enemies
	for (int i = 0; i < enemies.size(); i++) 
	{
		enemies[i]->Update(frametime);

		if (enemies[i]->isDead()) 
		{

			if (boss->isDead())
			{
				if (!gPortalSpawned)
				{
					gPortal->setPosition(2770, 670);

					gPortalSpawned = true;
				}

				enemies.pop_back();


			}
			else
			{
				delete enemies[i];

				enemies.erase(enemies.begin() + i);
				i--;
			}
			
		}
	}

	/* Condition to spawn Level 1 Boss */
	if (player->getX() > 2780 && !boss->isSpawned())
	{
		boss = new Boss1(tileMap);
		boss->setSpawn(true);
		boss->setPosition(2779, 653);
		enemies.push_back(boss);
	}

	if (player->getX() < 1500 && gPortalSpawned)
	{
		gPortalSpawned = false;

	}

	if (player->isDead())
	{
		std::ofstream outputFile("Resources/gameData/scores.txt", std::fstream::app);
		outputFile << player->getScore() << std::endl;
		outputFile.close();

		boss->setSpawn(false);
		enemies.clear();
		portals.clear();

		gPortalSpawned = false;


		/* Changing state to GameOverState */
		gsm.SetState(GameStateManager::GAMEOVER);
		gsm.Init();
	}

	if (gPortalSpawned)
	{
		gPortal->Update(frametime);

		if (player->intersects(*gPortal))
		{

			std::ofstream outputFile("Resources/gameData/tempScore.txt");
			outputFile << player->getScore() << std::endl;
			outputFile.close();

			boss->setSpawn(false);

			for (int i = 0; i < enemies.size(); i++)
			{
				delete enemies[i];

				enemies.erase(enemies.begin() + i);
				i--;
			}

			Boss1 *boss = new Boss1(tileMap);

			
			boss->setSpawn(false);
			
			//boss = NULL;

			portals.clear();

			gPortalSpawned = false;

			gsm.SetState(GameStateManager::LEVEL2STATE);
			gsm.Init();
		}
	}

}

void Level1State::Draw(sf::RenderWindow * window) 
{
	//draw background
	background.Draw(window);
	//draw tilemap
	tileMap.Draw(window);
	//draw player
	player->Draw(window);


	//draw portals
	for (int i = 0; i < portals.size(); i++)
	{
		portals[i]->Draw(window);
	}
	
	//draw health pickups
	for (int i = 0; i < heartPickups.size(); i++)
	{
		heartPickups[i]->Draw(window);

	}


	// draw bad heart pickups
	for (int i = 0; i < pHeartPickups.size(); i++)
	{
		pHeartPickups[i]->Draw(window);

	}
	
	//draw Fire pickups
	for (int i = 0; i < firePickups.size(); i++)
	{
		firePickups[i]->Draw(window);

	}
	
	window->draw(playerHealth);
	window->draw(playerScore);
	window->draw(playerFire);

	//draw enemies
	for (int i = 0; i < enemies.size(); i++) 
	{
		enemies[i]->Draw(window);
	}

	// draw Grand Portal
	if (gPortalSpawned)
	{
		gPortal->Draw(window);
	}

}

void Level1State::Init() 
{
	if (!font.loadFromFile("Resources/GOTHIC.TTF")) 
	{
		std::cout << "unable to load from file" << std::endl;
	}

	tileMap.LoadTiles("Resources/Tilesets/grasstileset.png");
	tileMap.LoadMap("Resources/Maps/one.txt");
	tileMap.setPosition((double)0, (double)0);
	
	// Player 
	player = new Player(tileMap);
	player->setPosition(50, 350);


	// Portals

	portal = new Portal(tileMap);
	portal->setPosition(200, 590);
	portals.push_back(portal);


	portal = new Portal(tileMap);
	portal->setPosition(570, 365);
	portals.push_back(portal);

	portal = new Portal(tileMap);
	portal->setPosition(924, 398);
	portals.push_back(portal);

	portal = new Portal(tileMap);
	portal->setPosition(1065, 330);
	portals.push_back(portal);
	// Portals ending



	// Pickups 

	//Heart
	heart = new Heart(tileMap);
	heart->setPosition(1961, 615);
	heartPickups.push_back(heart);

	heart = new Heart(tileMap);
	heart->setPosition(2318, 675);
	heartPickups.push_back(heart);

	heart = new Heart(tileMap);
	heart->setPosition(3207, 645);
	heartPickups.push_back(heart);

	//Purple Heart
	purpleheart = new PurpleHeart(tileMap);
	purpleheart->setPosition(776, 525);
	pHeartPickups.push_back(purpleheart);

	purpleheart = new PurpleHeart(tileMap);
	purpleheart->setPosition(2952, 795);
	pHeartPickups.push_back(purpleheart);

	//Fire 
	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(2203, 615);
	firePickups.push_back(firePickup);

	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(2353, 375);
	firePickups.push_back(firePickup);


	// Pickups ending



	// Enemies

	sss = new bouncer(tileMap);
	sss->setPosition(657, 405);
	enemies.push_back(sss);

	sss = new bouncer(tileMap);
	sss->setPosition(1584, 435);
	enemies.push_back(sss);

	s = new Slugger(tileMap);
	s->setPosition(1963, 380);
	s->setLeft(true);
	enemies.push_back(s);

	s = new Slugger(tileMap);
	s->setPosition(1978, 380);
	enemies.push_back(s);

	sss = new bouncer(tileMap);
	sss->setPosition(2250, 375);
	enemies.push_back(sss);

	sss = new bouncer(tileMap);
	sss->setPosition(2353, 375);
	enemies.push_back(sss);

	s = new Slugger(tileMap);
	s->setPosition(2700, 340);
	enemies.push_back(s);

	s = new Slugger(tileMap);
	s->setPosition(2772, 340);
	enemies.push_back(s);

	s = new Slugger(tileMap);
	s->setPosition(2900, 340);
	enemies.push_back(s);

	if (gPortalSpawned)
	{
		gPortalSpawned = false;
	}

	if (!gPortalSpawned)
	{
		//Boss1 *boss = new Boss1(tileMap);
		boss->setSpawn(false);
	}

}

void Level1State::KeyPressed(sf::Keyboard::Key key) 
{
	if (key == sf::Keyboard::Left) player->setLeft(true);
	if (key == sf::Keyboard::Right) player->setRight(true);
	if (key == sf::Keyboard::W) player->setJumping(true);
	if (key == sf::Keyboard::E) player->setGliding(true);
	if (key == sf::Keyboard::R) player->setScratching();
	if (key == sf::Keyboard::F) player->setFiring();
	if (key == sf::Keyboard::Escape) exit(0);


}

void Level1State::KeyReleased(sf::Keyboard::Key key) 
{
	if (key == sf::Keyboard::Left) player->setLeft(false);
	if (key == sf::Keyboard::Right) player->setRight(false);
	if (key == sf::Keyboard::W) player->setJumping(false);
	if (key == sf::Keyboard::E) player->setGliding(false);
}


void Level1State::ButtonPressed() {
	if (sf::Joystick::isConnected(0))
	{
		std::cout << "Joystick is connected" << "\n";

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) <= -100) //Left Analog Stick
			return player->setLeft(true);

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) >= 100) //Left Analog Stick
			return player->setRight(true);

		/*if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) < 0)
			player->setLeft(true);

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)> 0)
			player->setRight(true);*/

		if (sf::Joystick::isButtonPressed(0, 0)) //Button A
			player->setJumping(true);

		if (sf::Joystick::isButtonPressed(0, 1)) //Button B
			player->setFiring();

		if (sf::Joystick::isButtonPressed(0, 2))//Button X
			player->setScratching();


		if (sf::Joystick::isButtonPressed(0, 5))//Right Bumper
			player->setGliding(true);

		float PovX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
		std::cout << "PovX:" << PovX << std::endl;

		float PovY = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);
		std::cout << "PovY:" << PovY << std::endl;

	}
	else
	{
		std::cout << "Joystick is disconnected" << "\n";


	}
}


void Level1State::ButtonReleased()
{
	if (sf::Joystick::isConnected(0))
	{
		std::cout << "Joystick is connected" << "\n";

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) <= -100) //Left Analog Stick
			return player->setLeft(false);

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) >= 100) //Left Analog Stick
			return player->setRight(false);

		/*if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) < 0)
			player->setLeft(false);

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > 0)
			player->setRight(false);*/


		if (sf::Joystick::isButtonPressed(0, 13))
			player->setLeft(false);

		if (sf::Joystick::isButtonPressed(0, 14))
			player->setRight(false);


		if (sf::Joystick::isButtonPressed(0, 4)) //Left Bumper
			player->setUp(false);

		if (sf::Joystick::isButtonPressed(0, 9)) //Right Analog Stick
			player->setDown(false);

		if (sf::Joystick::isButtonPressed(0, 0)) //Button A
			player->setJumping(false);

		if (sf::Joystick::isButtonPressed(0, 5))//Right Bumper
			player->setGliding(false);

	}
	else
	{
		std::cout << "Joystick is disconnected" << "\n";

	}

}