#pragma once
#include "SceneGame.h"
class SceneBoss2 :public SceneGame
{
protected:
public:
	SceneBoss2();
	~SceneBoss2() override=default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

