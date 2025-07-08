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
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	item.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });
}

void Item::Update(float dt)
{
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(item);
	hitBox.Draw(window);
}

void Item::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Hill:
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


void Item::OnHeal(int heal)
{
	player->Heal(heal);
}

void Item::OnAmmo(int ammo)
{
	player->AddResrveAmmo(ammo);
}

void Item::OnAcceleration(int acceleration)
{
	player->AddSpeed(acceleration);
}



