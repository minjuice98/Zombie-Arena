#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "SceneGame.h"

class Player;
class Blood;

class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};

	static const int TotalTypes = 3;
	
protected:
	Types type = Types::Bloater;

	sf::Sprite body;
	std::string texId;
	sf::Vector2f direction;
	
	std::string name;
	int maxHp = 0;
	float speed = 0.f;
	int damage = 0;
	float attackInterval = 0.3f;
	int mpUp = 0;

	int hp;
	float attackTimer = 0.f;

	Player* player = nullptr;
	Blood* blood = nullptr;
	SceneGame* sceneGame = nullptr;
	TileMap* map = nullptr;

	HitBox hitBox;	

public:
	Zombie(const std::string& name = "");
	virtual ~Zombie() = default;

	sf::Vector2f GetPosition() const { return position; }
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);

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

	void OnDamage(int damage);
	int GetHp() {return hp;}
	void SetHp(int hp) { this->hp = hp; }
};