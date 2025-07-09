#pragma once
#include "SceneGame.h"
class SceneBoss2 :public SceneGame
{
protected:
	sf::Sprite boss;
	std::string texId = "graphics/Boss.png";
	sf::Vector2f direction;
	float speed = 0.f;
public:
	SceneBoss2();
	~SceneBoss2() override=default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};