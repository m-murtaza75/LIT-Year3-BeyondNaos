#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "TileMap.h"
#include "Background.h"
#include "Player.h"
#include "Slugger.h"
#include "Slime.h"
#include "bouncer.h"
#include "spikes.h"
#include "DemonBoss.h"
#include "EnemyFireBall.h"
#include "Portal.h"
#include "GrandPortal.h"
#include "Heart.h"
#include "PurpleHeart.h"
#include "FirePickup.h"
#include "Bat.h"


class Level2State : public GameState
{
public:
	class GameStateManager& gsm;
	Level2State(class GameStateManager& gsm);
	void Update(sf::RenderWindow* window, float frametime);
	void Draw(sf::RenderWindow* window);
	void Init();
	void KeyPressed(sf::Keyboard::Key key);
	void KeyReleased(sf::Keyboard::Key key);
	void readPlayerScore();
	
private:
	bool witchDead = true;
	TileMap tileMap;
	Background background;
	Player *player;
	DemonBoss *demonBoss = new DemonBoss(tileMap);
	Portal *portal;
	GrandPortal *gPortal = new GrandPortal(tileMap);
	Heart *heart;
	FirePickup *firePickup;
	PurpleHeart *purpleheart;
	std::vector<PurpleHeart*> pHeartPickups;
	std::vector<Heart*> heartPickups;
	std::vector<FirePickup*> firePickups;
	std::vector<Portal*> portals;
	std::vector<Enemy*> enemies;
	std::vector<EnemyFireBall*> efireBalls;
	Slugger *s;
	Bat *bat;
	EnemyFireBall *ef;
	EnemyFireBall *bossFire;
	Slime *ss;
	bouncer *sss;
	int health;
	int score;
	int maxFires;
	int fireLeft;
	int spawnDemon = 0;
	bool gPortalSpawned = false;
	sf::Font font;
	sf::Text playerHealth;
	sf::Text playerScore;
	sf::Text playerFire;
	spikes *spike;
};