#pragma once
#include "Scene.h"

class Player;
class Zombie;
class Blood;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	Zombie* zombie = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	std::list<Blood*> bloodList;
	std::list<Blood*> bloodPool;

	sf::Sprite cursor;

public:
	SceneIds Id;

	SceneGame();
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnZombies(int count);
	void SpawnBlood(const sf::Vector2f& pos);
	void Skill();

	const std::list<Zombie*>& GetZombies() const 
	{
		return zombieList;
	}
	const std::list<Blood*>& GetBlood() const
	{
		return bloodList;
	}
};