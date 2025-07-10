#pragma once
#include "SceneGame.h"

class SceneWave1 : public SceneGame
{
protected:
public:
	SceneWave1();
	~SceneWave1() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};