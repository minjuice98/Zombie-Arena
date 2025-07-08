#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneGame;
class Bullet;

class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/player.png";

	sf::Vector2f direction;
	sf::Vector2f look;

	float speed = 500.f;

	SceneGame* sceneGame = nullptr;

	HitBox hitBox;

	std::list<Bullet*> bulletList;
	std::list<Bullet*> bulletPool;

	float shootInterval = 0.1f;
	float shootTimer = 0.f;

	int hp = 0;
	int maxHp = 100;

	const int MAX_MAG = 10; //쏠수잇는최대값
	int currentAmmo = 10; //남아있는값 현재 가지고있는값
	int resrveAmmo = 60; //가지고있는



public:
	bool IsAlive() const { return hp > 0; }

	Player(const std::string& name = "");
	~Player() override = default;


	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	int GetHp() const { return hp; };
	void Heal(int amount);
	int GetResrveAmmo() const{ return resrveAmmo; };
	void AddResrveAmmo(int ammo);
	int GetSpeed() const { return speed; };
	void AddSpeed(int s);
	 

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	const HitBox& GetHitBox() const
	{
		return hitBox;
	}

	void Shoot();
	void OnDamage(int damage);
};

