#pragma once
#include "SceneGame.h"
#include "HitBox.h"

class SceneBoss2 : public SceneGame
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
	float attackTimer = 0.f;

	HitBox hitBox;

	sf::RectangleShape bossHpBar;
	sf::Text bossHpText;
	const float BOSS_HP_BAR_WIDTH = 400.f;
	const float BOSS_HP_BAR_HEIGHT = 30.f;

	bool isCleared = false;
	sf::Text clearText;
	sf::Text scoreText;

public:
	SceneBoss2();
	~SceneBoss2() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnDamage(int damage);
	int GetHp() { return hp; }
	void SetHp(int hp) { this->hp = hp; }

	sf::FloatRect GetBossGlobalBounds() const { return boss.getGlobalBounds(); }
	const HitBox& GetBossHitBox() const { return hitBox; }

	void UpdateBossHpUI();
	void SetupClearUI();
};