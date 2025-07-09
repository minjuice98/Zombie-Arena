#pragma once
#include "Scene.h"

class Player;
class Zombie;
class GameUI;
class TileMap;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	GameUI* ui = nullptr;
	TileMap* map = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	sf::Sprite cursor;

	int stageLevel = 1;
	int score = 0;
	int zombieCount = 0;

public:
	SceneGame();
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnZombies(int count, float radius);

	const std::list<Zombie*>& GetZombies() const 
	{
		return zombieList;
	}
};

