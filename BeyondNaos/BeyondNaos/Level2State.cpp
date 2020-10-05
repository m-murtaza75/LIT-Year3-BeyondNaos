#include "Level2State.h"


Level2State::Level2State(GameStateManager & gsm) : gsm(gsm), tileMap(30), background("Resources/Backgrounds/rockyworld.gif", 0.5) 
{
	//Init();
}

void Level2State::Update(sf::RenderWindow * window, float frametime) 
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


	tileMap.setPosition(((WINWIDTH*WINSCALE) / 2 - player->getX()), ((WINHEIGHT*WINSCALE) / 2 - player->getY()));
	background.setPosition(tileMap.getX(), tileMap.getY());



	//attack enemies
	player->checkAttack(enemies);


	//update all enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update(frametime);

		if (enemies[i]->isFiring())
		{
			int firePosx = enemies[i]->getX();
			int firePosy = enemies[i]->getY();

			if (demonBoss->isFiring())
			{
				if (!demonBoss->isFireSpawned())
				{
					bossFire = new EnemyFireBall(tileMap, true);
					bossFire->setPosition(firePosx - 12, firePosy + 30);

					demonBoss->setFireSpawned(true);
				}

				if (demonBoss->isFireSpawned())
				{
					bossFire->Update(frametime);

					if (player->intersects(*bossFire))
					{
						player->hit(demonBoss->getDamage());
						bossFire->setHit();
					}

					if (bossFire->shouldRemove())
					{
						demonBoss->setFireSpawned(false);

						demonBoss->setFiring(false);

						delete bossFire;
					}
				}
			}
			else
			{

				if (!enemies[i]->isFireSpawned())
				{
					ef = new EnemyFireBall(tileMap, true);
					ef->setPosition(firePosx + 12, firePosy + 30);

					efireBalls.push_back(ef);

					enemies[i]->setFireSpawned(true);
				}

				if (enemies[i]->isFireSpawned())
				{
					for (int i = 0; i < efireBalls.size(); i++)
					{
						efireBalls[i]->Update(frametime);

						if (player->intersects(*efireBalls[i]))
						{
							player->hit(enemies[i]->getDamage());
							efireBalls[i]->setHit();
						}

						if (efireBalls[i]->shouldRemove())
						{


							enemies[i]->setFireSpawned(false);

							enemies[i]->setFiring(false);

							delete efireBalls[i];

							efireBalls.erase(efireBalls.begin() + i);
							i--;

						}

					}
				}
			}

		}

		if (enemies[i]->isDead())
		{
			if (demonBoss->isDead())
			{
				witchDead = true;

				if (!gPortalSpawned)
				{
					gPortal->setPosition(2747, 1120);

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

	if (player->getX() < 1000 && gPortalSpawned)
	{
		gPortalSpawned = false;
	}


	/* Handling player death */
	if (player->isDead())
	{
		std::ofstream outputFile("Resources/gameData/scores.txt", std::fstream::app);
		outputFile << player->getScore() << std::endl;
		outputFile.close();


		enemies.clear();
		portals.clear();
		efireBalls.clear();

		gPortalSpawned = false;

		spawnDemon = 0;

		/* Changing state to GameOverState */
		gsm.SetState(GameStateManager::GAMEOVER);
		gsm.Init();
	}

	/* Condition to check if player touches Grand-portal */
	if (gPortalSpawned)
	{
		gPortal->Update(frametime);

		if (player->intersects(*gPortal))
		{

			std::ofstream outputFile("Resources/gameData/tempScore.txt");
			outputFile << player->getScore() << std::endl;
			outputFile.close();
			

			for (int i = 0; i < enemies.size(); i++)
			{
				delete enemies[i];

				enemies.erase(enemies.begin() + i);
				i--;
			}

			DemonBoss *demonBoss = new DemonBoss(tileMap);
			demonBoss->setSpawn(false);

			portals.clear();
			efireBalls.clear();

			gPortalSpawned = false;


			spawnDemon = 0;


			gsm.SetState(GameStateManager::LEVEL3STATE);
			gsm.Init();
		}
	}

	/*int x = player->getX();   
	int y = player->getY();*/

}

void Level2State::Draw(sf::RenderWindow * window)
{
	//draw background
	background.Draw(window);
	//draw tilemap
	tileMap.Draw(window);
	//draw player
	player->Draw(window);

	window->draw(playerHealth);
	window->draw(playerScore);
	window->draw(playerFire);

	//draw portals
	for (int i = 0; i < portals.size(); i++)
	{
		portals[i]->Draw(window);
	}

	//draw enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Draw(window);

		if (enemies[i]->isFiring())
		{
			if (demonBoss->isFiring())
			{
				bossFire->Draw(window);
			}
			else
			{

				for (int i = 0; i < efireBalls.size(); i++)
				{
					efireBalls[i]->Draw(window);
				}
			}

		}
	}

	/* Condition to spawn Boss */

	if (player->getX() > 2405 && player->getY() > 1100 && spawnDemon == 0)
	{
		demonBoss = new DemonBoss(tileMap);
		demonBoss->setPosition(2747, 1120);
		enemies.push_back(demonBoss);

		spawnDemon = 1;
	}

		
	// draw Grand Portal
	if (gPortalSpawned)
	{
		gPortal->Draw(window);
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

}

void Level2State::Init()
{
	//gPortalSpawned = false;

	if (!font.loadFromFile("Resources/GOTHIC.TTF"))
	{
		std::cout << "unable to load from file" << std::endl;
	}

	tileMap.LoadTiles("Resources/Tilesets/rocktileset.png");
	tileMap.LoadMap("Resources/Maps/two.txt");
	tileMap.setPosition((double)0, (double)0);
	player = new Player(tileMap);
	player->setPosition(95, 350);
	player->setDead(false);

	/* Getting player score from level 1 */
	readPlayerScore();



	/****  Enemies *****/

	bat = new Bat(tileMap);
	bat->setPosition(323, 688);
	enemies.push_back(bat);
	
	bat = new Bat(tileMap);
	bat->setPosition(1629, 1100);
	enemies.push_back(bat);


	sss = new bouncer(tileMap);
	sss->left = true;
	sss->setPosition(574, 1065);
	enemies.push_back(sss);

	sss = new bouncer(tileMap);
	sss->left = true;
	sss->setPosition(240, 525);
	enemies.push_back(sss);

	sss = new bouncer(tileMap);
	sss->left = true;
	sss->setPosition(1716, 455);
	enemies.push_back(sss);



	s = new Slugger(tileMap);
	s->left = true;
	s->setPosition(300, 510);
	enemies.push_back(s);

	s = new Slugger(tileMap);
	s->setPosition(1890, 600);
	enemies.push_back(s);

	s = new Slugger(tileMap);
	s->setPosition(1110, 420);
	enemies.push_back(s);

	
	spike = new spikes(tileMap);
	spike->setPosition(300, 550);
	enemies.push_back(spike);

	spike = new spikes(tileMap);
	spike->setPosition(340, 550);
	enemies.push_back(spike);
	
	spike = new spikes(tileMap);
	spike->setPosition(1735, 1335);
	enemies.push_back(spike);

	spike = new spikes(tileMap);
	spike->setPosition(1725, 1335);
	enemies.push_back(spike);


	ss = new Slime(tileMap);
	ss->left = true;
	ss->setPosition(802, 1075);
	enemies.push_back(ss);

	ss = new Slime(tileMap);
	ss->left = true;
	ss->setPosition(1238, 1335);
	enemies.push_back(ss);

	



	// Fire Pickup
	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(424, 1245);
	firePickups.push_back(firePickup);

	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(2411, 1305);
	firePickups.push_back(firePickup);

	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(2425, 1090);
	firePickups.push_back(firePickup);



	// Health Pickup
	heart = new Heart(tileMap);
	heart->setPosition(903, 1245);
	heartPickups.push_back(heart);
	
	heart = new Heart(tileMap);
	heart->setPosition(1605, 525);
	heartPickups.push_back(heart);

	// Purple Pickup
	purpleheart = new PurpleHeart(tileMap);
	purpleheart->setPosition(1674, 1179);
	pHeartPickups.push_back(purpleheart);


	//Portals 
	portal = new Portal(tileMap);
	portal->setPosition(1719, 1290);
	portals.push_back(portal);

	portal = new Portal(tileMap);
	portal->setPosition(2095, 1230);
	portals.push_back(portal);

	if (gPortalSpawned)
	{
		gPortalSpawned = false;
	}


}

void Level2State::KeyPressed(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Left) player->setLeft(true);
	if (key == sf::Keyboard::Right) player->setRight(true);
	if (key == sf::Keyboard::Up) player->setUp(true);
	if (key == sf::Keyboard::Down) player->setDown(true);
	if (key == sf::Keyboard::W) player->setJumping(true);
	if (key == sf::Keyboard::E) player->setGliding(true);
	if (key == sf::Keyboard::R) player->setScratching();
	if (key == sf::Keyboard::F) player->setFiring();
	if (key == sf::Keyboard::Escape) exit(0);

}

void Level2State::KeyReleased(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Left) player->setLeft(false);
	if (key == sf::Keyboard::Right) player->setRight(false);
	if (key == sf::Keyboard::Up) player->setUp(false);
	if (key == sf::Keyboard::Down) player->setDown(false);
	if (key == sf::Keyboard::W) player->setJumping(false);
	if (key == sf::Keyboard::E) player->setGliding(false);
}

void Level2State::readPlayerScore()
{
	std::ifstream readFile("Resources/gameData/tempScore.txt");

	int score = 0;

	readFile >> score;

	player->updateScore(score);

}