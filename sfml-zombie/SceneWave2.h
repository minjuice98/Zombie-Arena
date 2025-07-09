#pragma once
#include "SceneGame.h"

class SceneWave2 : public SceneGame
{
protected:

public:
	SceneWave2();
	~SceneWave2() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

