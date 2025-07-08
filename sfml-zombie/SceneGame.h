#pragma once
#include "Scene.h"

class Player;
class Zombie;
class Item;
class TileMap;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tileMap = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	std::list<Item*> itemList;
	std::list<Item*> itemPool;

	sf::Sprite cursor;

public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnZombies(int count);
	void SpawnItems(int count);//좀비가아닌 타임으로 ? 

	const std::list<Zombie*>& GetZombies() const 
	{
		return zombieList;
	}


	const std::list<Item*>& GetItems() const
	{
		return itemList;
	}

};

