#pragma once
#include "Scene.h"

class Player;
class Zombie;
class GameUI;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	GameUI* ui = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	sf::Sprite cursor;

	int stageLevel = 1;

public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnZombies(int count);

	const std::list<Zombie*>& GetZombies() const 
	{
		return zombieList;
	}
};

