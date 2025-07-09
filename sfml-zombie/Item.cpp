#include "stdafx.h"
#include "Item.h"
#include "Player.h"


Item::Item(const std::string& name)
	: GameObject(name)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	item.setPosition(pos);
}

void Item::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	item.setRotation(rot);
}

void Item::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	item.setScale(s);
}

void Item::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	item.setOrigin(o);
}

void Item::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(item, preset);
	}
}

void Item::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetType(type);
}

void Item::Release()
{
}

void Item::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");//
	item.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	GenerationTime = 0.f;
}

void Item::Update(float dt)//히트박스
{
	hitBox.UpdateTransform(item, GetLocalBounds());

	GenerationTime += dt;
	if (GenerationTime > GenerationInterval)
	{
		if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
		{
			this->ActiveType();
			SetActive(false);
		}

	}




}

void Item::Draw(sf::RenderWindow& window)
{
	if (GenerationTime > GenerationInterval)
	{
		window.draw(item);
		hitBox.Draw(window);
	}
}

void Item::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Heal:
		texId = "graphics/health_pickup.png";
		break;
	case Types::Ammo:
		texId = "graphics/ammo_pickup.png";
		break;
	case Types::Acceleration:
		texId = "graphics/acceleration.png";

		break;
	}
}

void Item::ActiveType()
{

	switch (type)
	{
	case Types::Heal:
		player->Heal(100);
		break;
	case Types::Ammo:
		player->AddResrveAmmo(10);
		break;
	case Types::Acceleration:
		player->AddSpeed(50);
		break;
	}
}



