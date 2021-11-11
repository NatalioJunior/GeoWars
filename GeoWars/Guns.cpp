#include "Guns.h" 
#include "Missile.h"
#include "GeoWars.h"

Guns::Guns() {
	sprite = new Sprite("Resources/Turret.png");
	speed = new Vector(0.0f, 0.0f);
}

Guns::~Guns() {
	delete sprite;
}

void Guns::Update() {
	MoveTo(GeoWars::player->X(), GeoWars::player->Y());

	float delta = 240.0f * gameTime;

	if (window->KeyDown('O'))
		speed->Rotate(delta);
	if (window->KeyDown('P'))
		speed->Rotate(-delta);
	if (window->KeyPress('K')) {
		float ypy = speed->Angle();
	}

	// dispara míssil
	if (window->KeyPress(VK_SPACE))
	{
		GeoWars::audio->Play(FIRE);
		GeoWars::scene->Add(new Missile(), STATIC);
	}
}

inline void Guns::Draw()
{
	sprite->Draw(GeoWars::player->X(), GeoWars::player->Y(), Layer::UPPER, scale, speed->Angle());
}

// ------------------------------------------------------------------------------