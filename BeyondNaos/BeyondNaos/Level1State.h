 #pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "TileMap.h"
#include "Background.h"
#include "Player.h"
#include "Boss1.h"
#include "Slugger.h"
#include "Bat.h"
#include "EnemyFireBall.h"
#include "Portal.h"
#include "GrandPortal.h"
#include "Heart.h"
#include "FirePickup.h"
#include "bouncer.h"
#include "spikes.h"
#include "PurpleHeart.h"


class Level1State: public GameState 
{
public:
	class GameStateManager& gsm;
	Level1State(class GameStateManager& gsm);
	void Update(sf::RenderWindow* window, float frametime);
	void Draw(sf::RenderWindow* window);
	void Init();
	void KeyPressed(sf::Keyboard::Key key);
	void KeyReleased(sf::Keyboard::Key key);
	void ButtonPressed();
	void ButtonReleased();

private:
	TileMap tileMap;
	Background background;
	Player *player;
	Boss1 *boss = new Boss1(tileMap);
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
	Slugger *s;
	Bat *bat;
	int health;
	int score;
	int maxFires;
	int fireLeft;
	bool gPortalSpawned = false;
	sf::Font font;
	sf::Text playerHealth;
	sf::Text playerScore;
	sf::Text playerFire;
	bouncer *sss;
	spikes *spike;

};