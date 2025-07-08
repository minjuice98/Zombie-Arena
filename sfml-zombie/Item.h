#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Player;

class Item :   public GameObject
{

public:
	enum class Types
	{
		Heal,
		Ammo,
		Acceleration,
	};
	//투명화 or 슬로우 가능여부

	static const int TotalTypes = 3;

protected:
	Types type = Types::Heal;

	sf::Sprite item;
	std::string texId;

	float Generation_Time = 0.f;
	Player* player = nullptr;
	
	HitBox hitBox;

public:	
	Item(const std::string& name = "");
	virtual ~Item() = default;

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
		return item.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return item.getGlobalBounds();
	}

	const HitBox& GetHitBox() const
	{
		return hitBox;
	}

	void OnHeal(int heal);

	void OnAmmo(int ammo);

	void OnAcceleration(int acceleration);









};

