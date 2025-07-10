#pragma once
#include "Scene.h"

class SceneUpgrade : public Scene
{
protected:
	sf::Sprite background;
	sf::Text hpUpgradeMessage;
	sf::Text pickupUpgradeMessage;
	sf::Text speedUpgradeMessage;

	sf::Sprite cursor;

public:
	static int hpUpgradeCount;
	static int pickupUpgradeCount;
	static int speedUpgradeCount;
	static SceneIds nextSceneId;

	SceneUpgrade();
	~SceneUpgrade() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};