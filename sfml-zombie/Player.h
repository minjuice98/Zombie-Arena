#pragma once
#include "GameObject.h"
#include "HitBox.h"

class GameUI;
class SceneGame;
class Bullet;
class TileMap;

class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/player.png";

	sf::Vector2f direction;
	sf::Vector2f look;

	float speed = 200.f;
	float MaxSpeed = 550.f;

	SceneGame* sceneGame = nullptr;
	GameUI* ui = nullptr;
	TileMap* map = nullptr;

	HitBox hitBox;

	std::list<Bullet*> bulletList;
	std::list<Bullet*> bulletPool;

	float shootInterval = 0.33f;
	float shootTimer = 0.f;

	int hp = 0;
	int mp = 0;
	int maxHp = 100;

	const int MAX_MAG = 12;
	const int INITIAL_AMMO = 24;
	int currentAmmo = MAX_MAG;
	int reserveAmmo = INITIAL_AMMO;

	int minX;
	int minY;
	int maxX;
	int maxY;

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
	int GetResrveAmmo() const{ return reserveAmmo; };
	void AddResrveAmmo(int ammo);
	float GetSpeed() const { return speed; };
	void AddSpeed(int s);
	 
	void MaxHpUp(int plus) { maxHp += plus; }

	int GetCurrentAmmo() const { return currentAmmo; }
	int GetReserveAmmo() const { return reserveAmmo; }

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

	int GetMp() { return mp; };
	void SetMp(int mp) { this->mp = mp; }
};