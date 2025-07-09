#pragma once
#include "SceneGame.h"

class SceneBoss2 :public SceneGame
{
protected:

	sf::Sprite boss;
	std::string texId = "graphics/Boss.png";
	sf::Vector2f direction;
	int maxHp = 1000;
	float speed = 100.f;
	int damage = 50;
	int hp;
	float attackInterval = 0.3f;
	

public:
	SceneBoss2();
	~SceneBoss2() override=default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void onDamage(int damage);
	int GetHp() { return hp; }
	void SetHp(int hp) { this->hp = hp; }
};