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

	int stageLevel = 1;
	int score = 0;
	int zombieCount = 0;

	float GenerationInterval = 8.f;

	float GenerationTime = 0.f;

public:
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
	void SpawnZombies(int count, float radius);

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
};