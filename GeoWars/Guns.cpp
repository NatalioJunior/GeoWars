#include "Guns.h"
#include "GeoWars.h"

Player*& Guns::player = GeoWars::player;

Guns::Guns(uint GunType) {
	switch (GunType)
	{
	case HANDGUN: tileset = new TileSet("Resources/HandGun.png", 55, 43, 2, 2);
		anim = new Animation(tileset, 1.0f, true);
		break;
	}
	
	speed = new Vector(180.0f, 0.0f);

	uint left[1] = { 1 };
	uint right[1] = { 2 };

	anim->Add(INVERTED, right, 1);
	anim->Add(NORMAL, left, 1);
	MoveTo(player->X(), player->Y());
}

Guns::~Guns() {
	delete anim;
	delete tileset;
}

void Guns::Update() {
	float delta = 240.0f * gameTime;

	if (window->KeyDown('O'))
		Rotate(0.5f * delta);
	if (window->KeyDown('P'))
		Rotate(-0.5f * delta);
	if (window->KeyPress('K'))
		float xpx = Rotation();

	if (Rotation() > 90.0f && Rotation() < 270.0f)
		anim->Select(INVERTED);
	if (Rotation() <= 90.0f || Rotation() >= 270.0f)
		anim->Select(NORMAL);

	if (Rotation() > 360.0f)
		RotateTo(Rotation() - 360.0f);
	if (Rotation() < 0)
		RotateTo(Rotation() + 360.0f);
}

inline void Guns::Draw()
{
	anim->Draw(player->X(), player->Y(), Layer::UPPER, scale, rotation);
}

// ------------------------------------------------------------------------------