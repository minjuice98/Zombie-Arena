#pragma once
#include "GameObject.h"

class Player;

class GameUI : public GameObject
{
protected:
	sf::Text scoreMessage;
	sf::Text ammoMessage;
	sf::Text stageInfoMessage;
	sf::Text manaMessage;

	sf::Sprite ammoIcon;

	sf::RectangleShape hpBar;

	std::string ammoTexId = "graphics/ammo_icon.png";
	std::string fontId = "fonts/zombiecontrol.ttf";

	int stageLevel = 1;
	const float BAR_SIZE = 250.f;

	Player* player = nullptr;

public:
	GameUI(const std::string& name = "");
	virtual ~GameUI() = default;

	void SetPlayer(Player* p) { player = p; }
	void SetStageLevel(int l) { stageLevel = l; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateAmmoMessage();
	void UpdateScoreMessage(int s);
	void UpdateZombieCountMessage(int count);
	void UpdateHpBar(int maxHp, int hp);
	void UpdateManaMessage(int mp);
};