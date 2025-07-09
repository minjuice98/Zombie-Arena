#pragma once
#include "GameObject.h"
class Zombie;
class Blood : public GameObject
{
protected:
	sf::Sprite blood;
	std::string texId = "graphics/blood.png";

	sf::Vector2f bloodPos;
	Zombie* zombie=nullptr;

	float time = 0.f;//누적시간
	const float maxTime = 10.f; //핏자국 유효시간

public:
	Blood(const std::string& name = "");
	virtual ~Blood() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Reset(const sf::Vector2f& pos);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetLocalBounds() const override
	{
		return blood.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return blood.getGlobalBounds();
	}
};