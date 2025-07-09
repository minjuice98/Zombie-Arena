#pragma once
#include "Scene.h"
class GameOver :    public Scene
{
protected:
	sf::Sprite background;
	sf::Text deathMessage;
	sf::Text restartMessage;
	sf::Text exitMessage;	

	sf::Sprite cursor;

public:
	GameOver();
	~GameOver() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

