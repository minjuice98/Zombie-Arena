#pragma once
#include "Scene.h"

class Player;
class Zombie;
class Blood;
class GameUI;
class Item;
class TileMap;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	GameUI* ui = nullptr;
	TileMap* map = nullptr;
	Zombie* zombie = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	std::list<Blood*> bloodList;
	std::list<Blood*> bloodPool;

	std::list<Item*> itemList;
	std::list<Item*> itemPool;

	sf::Sprite cursor;

	sf::Text PauseMessage;
	sf::Text AgainMessage;
	sf::Text ExitMessage;		

	
	int stageLevel = 1;
	int zombieCount = 0;

	float GenerationInterval = 3.f;	
	float GenerationTime = 0.f;

	sf::RectangleShape flashEffect;
	float flashDuration = 0.1f;  
	float flashTimer = 0.f;    
	bool isFlashing = false;
	

	bool pause = false;

public:
	static int score;
	SceneGame();
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnItems(int count);
	void SpawnBlood(const sf::Vector2f& pos);
	void Skill();
	void SpawnZombies(int count);
	void PauseMenu();

	void StageClear();

	const std::list<Zombie*>& GetZombies() const 
	{
		return zombieList;
	}
	const std::list<Blood*>& GetBlood() const
	{
		return bloodList;
	}
	const std::list<Item*>& GetItems() const
	{
		return itemList;
	}

	void ApplyUpgrade();
};