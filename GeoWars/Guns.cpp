#include "Guns.h" 
#include "Missile.h"
#include "GeoWars.h"

Guns::Guns(uint GunType) {
	switch (GunType)
	{
	case HANDGUN: tileset = new TileSet("Resources/HandGun.png", 55, 43, 2, 2);
		anim = new Animation(tileset, 1.0f, true);
		break;
	}
	
	speed = new Vector(0.0f, 0.0f);

	uint left[1] = { 1 };
	uint right[1] = { 2 };

	anim->Add(INVERTED, right, 1);
	anim->Add(NORMAL, left, 1);
	MoveTo(GeoWars::player->X(), GeoWars::player->Y());
}

Guns::~Guns() {
	delete anim;
	delete tileset;
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

	if (speed->Angle() > 90.0f && speed->Angle() < 270.0f)
		anim->Select(INVERTED);
	if (speed->Angle() <= 90.0f || speed->Angle() >= 270.0f)
		anim->Select(NORMAL);

	// dispara míssil
	if (window->KeyPress(VK_SPACE))
	{
		GeoWars::audio->Play(FIRE);
		GeoWars::scene->Add(new Missile(), STATIC);
	}
}

inline void Guns::Draw()
{
	anim->Draw(x, y, Layer::UPPER, scale, speed->Angle());
}

// ------------------------------------------------------------------------------