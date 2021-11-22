#include "Explosion.h"
#include "GeoWars.h"

// ------------------------------------------------------------------------------

Explosion::Explosion(float pX, float pY)
{
	MoveTo(pX, pY);
	tileset = new TileSet("Resources/explosion.png", 9, 9);
	anim = new Animation(tileset, 0.01f, false);
	GeoWars::audio->Play(EXPLODE);
}

// ------------------------------------------------------------------------------

Explosion::~Explosion()
{
	delete tileset;
	delete anim;

}

// -------------------------------------------------------------------------------

void Explosion::Update()
{
	anim->NextFrame();
	if (anim->Inactive()) {
		GeoWars::scene->Delete();
	}
}

void Explosion::Draw() {
	anim->Draw(x, y, Layer::LOWER, scale, rotation - 90.0f);
}
// -------------------------------------------------------------------------------
