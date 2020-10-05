#include "Level3State.h"


Level3State::Level3State(GameStateManager & gsm) : gsm(gsm), tileMap(30), background("Resources/Backgrounds/castlebg.gif", 0.5)
{
	//Init();
}

void Level3State::Update(sf::RenderWindow * window, float frametime)
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

		if (enemies[i]->isDead())
		{
			delete enemies[i];

			enemies.erase(enemies.begin() + i);
			i--;
		}
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

		spawnWitch = 0;

		witchDead = true;

		delete witch;

		witch = new Witch(tileMap);

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

			std::ofstream outputFile("Resources/gameData/scores.txt", std::fstream::app);
			outputFile << player->getScore() << std::endl;
			outputFile.close();


			for (int i = 0; i < enemies.size(); i++)
			{
				delete enemies[i];

				enemies.erase(enemies.begin() + i);
				i--;
			}

			portals.clear();
			efireBalls.clear();

			gPortalSpawned = false;

			spawnWitch = 0;

			witchDead = true;

			delete witch;

			witch = new Witch(tileMap);

			gsm.SetState(GameStateManager::GAMECOMPLETION);
			gsm.Init();
		}
	}


	handleBoss(frametime);
	 
	int x = player->getX();
	int y = player->getY();


}


void Level3State::Draw(sf::RenderWindow * window)
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
			for (int i = 0; i < efireBalls.size(); i++)
			{
				efireBalls[i]->Draw(window);
			}

		}
	}


	if (!witchDead)
	{
		witch->Draw(window);

		if (witch->isFiring())
		{
			wfb->Draw(window);
		}
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


void Level3State::Init()
{

	gPortalSpawned = false;

	if (!font.loadFromFile("Resources/GOTHIC.TTF"))
	{
		std::cout << "unable to load from file" << std::endl;
	}

	tileMap.LoadTiles("Resources/Tilesets/castletileset.png");
	tileMap.LoadMap("Resources/Maps/three.txt");
	tileMap.setPosition((double)0, (double)0);
	player = new Player(tileMap);
	player->setPosition(162, 1365);
	player->setDead(false);

	/* Getting player score */
	readPlayerScore();



	/****  Enemies *****/  

	
	bat = new Bat(tileMap);
	bat->setPosition(431, 1035);
	enemies.push_back(bat);

	bat = new Bat(tileMap);
	bat->setPosition(1257,  971);
	enemies.push_back(bat);

	bat = new Bat(tileMap);
	bat->setPosition(2079, 964);
	enemies.push_back(bat);



	sss = new bouncer(tileMap);
	sss->setPosition(2282, 1305);
	enemies.push_back(sss);

	sss = new bouncer(tileMap);
	sss->setPosition(1038, 1095);
	enemies.push_back(sss);


	s = new Slugger(tileMap);
	s->setPosition(831, 515);
	s->setLeft(true);
	enemies.push_back(s);

	s = new Slugger(tileMap);
	s->setPosition(1148, 805);
	s->setLeft(true);
	enemies.push_back(s);

	sp = new spider(tileMap);
	sp->setPosition(1957, 805);
	enemies.push_back(sp);

	sp = new spider(tileMap);
	sp->setPosition(2534, 955);
	enemies.push_back(sp);
	

	ss = new Slime(tileMap);
	ss->left = true;
	ss->setPosition(391, 795);
	enemies.push_back(ss);

	ss = new Slime(tileMap);
	ss->left = true;
	ss->setPosition(535, 205);
	enemies.push_back(ss);
	
	spike = new spikes(tileMap);
	spike->setPosition(923, 315);
	enemies.push_back(spike);

	spike = new spikes(tileMap);
	spike->setPosition(2596, 825);
	enemies.push_back(spike);

	spike = new spikes(tileMap);
	spike->setPosition(2600, 825);
	enemies.push_back(spike);

	
	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(394, 525);
	firePickups.push_back(firePickup);

	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(1250, 225);
	firePickups.push_back(firePickup);

	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(795, 405);
	firePickups.push_back(firePickup);

	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(1881, 945);
	firePickups.push_back(firePickup);

	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(1930, 225);
	firePickups.push_back(firePickup);

	firePickup = new FirePickup(tileMap);
	firePickup->setPosition(2202, 345);
	firePickups.push_back(firePickup);


	heart = new Heart(tileMap);
	heart->setPosition(757, 795);
	heartPickups.push_back(heart);

	
	heart = new Heart(tileMap);
	heart->setPosition(2791, 705);
	heartPickups.push_back(heart);

	

	heart = new Heart(tileMap);
	heart->setPosition(1526, 975);
	heartPickups.push_back(heart);

	heart = new Heart(tileMap);
	heart->setPosition(2320, 225);
	heartPickups.push_back(heart);


	purpleheart = new PurpleHeart(tileMap);
	purpleheart->setPosition(165, 405);
	pHeartPickups.push_back(purpleheart);

	purpleheart = new PurpleHeart(tileMap);
	purpleheart->setPosition(2320, 1155);
	pHeartPickups.push_back(purpleheart);

	purpleheart = new PurpleHeart(tileMap);
	purpleheart->setPosition(967, 315);
	pHeartPickups.push_back(purpleheart);

	
	portal = new Portal(tileMap);
	portal->setPosition(119, 795);
	portals.push_back(portal);

	portal = new Portal(tileMap);
	portal->setPosition(1942, 555);
	portals.push_back(portal);


	
	
	
}

void Level3State::KeyPressed(sf::Keyboard::Key key) 
{
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

void Level3State::KeyReleased(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Left) player->setLeft(false);
	if (key == sf::Keyboard::Right) player->setRight(false);
	if (key == sf::Keyboard::Up) player->setUp(false);
	if (key == sf::Keyboard::Down) player->setDown(false);
	if (key == sf::Keyboard::W) player->setJumping(false);
	if (key == sf::Keyboard::E) player->setGliding(false);
}

void Level3State::readPlayerScore()
{
	std::ifstream readFile("Resources/gameData/tempScore.txt");

	int score = 0;

	readFile >> score;

	player->updateScore(score);

}



void Level3State::handleBoss(float frametime)
{
	/* Condition to spawn Witch Boss */
	if ((player->getX() > 1982 && player->getY() <= 556) && spawnWitch == 0)
	{
		witch->setLeft(true);
		witch->setPosition(2550, 528);

		witchDead = false;

		spawnWitch = 1;
	}

	if (!witchDead)
	{
		witch->Update(frametime);

		//Check player attacking witch
		player->checkAttackOnWitch(witch);

		if (witch->isFiring())
		{
			int firePosx = witch->getX();
			int firePosy = witch->getY();

			if (!witch->isFireSpawned())
			{
				wfb = new WitchFireBall(tileMap, true);
				wfb->setPosition(firePosx - 12, firePosy + 30);

				//efireBalls.push_back(ef);

				witch->setFireSpawned(true);
			}

			if (witch->isFireSpawned())
			{
				wfb->Update(frametime);

				if (player->intersects(*wfb))
				{
					player->hit(witch->getDamage());
					wfb->setHit();
				}

				if (wfb->shouldRemove())
				{
					witch->setFireSpawned(false);

					witch->setFiring(false);

					delete wfb;
				}
			}
		}

		if (witch->isDead())
		{
			witchDead = true;

			if (!gPortalSpawned)
			{
				gPortal->setPosition(2580, 520);
				gPortalSpawned = true;
			}

			delete witch;

			witch = new Witch(tileMap);

		}

	}

}