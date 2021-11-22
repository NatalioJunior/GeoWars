
#include "WallHit.h"
#include "GeoWars.h"
#include "Light.h"
#include "PlasmaBall.h"
// ------------------------------------------------------------------------------



PlasmaBall::PlasmaBall(float pX, float pY, float angle, float scale)
{
	scaleF = scale;
	// inicializa sprite
	sprite = new Sprite("Resources/Bullet.png");
	tileset = new TileSet("Resources/plasmaball_pixelart.png", 2, 1);
	anim = new Animation(tileset, 0.5f, true);
	// cria bounding box
	BBox(new Circle(8 * scaleF));
	// speed.RotateTo(-player->gun->speed->Angle() - 180.0f);
	speed.RotateTo(angle);
	speed.ScaleTo(7.0f);

	// move para posição
	MoveTo(pX,pY);

	//RotateTo(player->gun->speed->Angle() - 180.0f);
	RotateTo(-angle);
	
	// define tipo
	// define tipo
	type = MISSILE;
}

// ------------------------------------------------------------------------------

PlasmaBall::~PlasmaBall()
{
	delete sprite;
	delete tileset;
	delete anim;
}

// -------------------------------------------------------------------------------

void PlasmaBall::Update()
{
	// move míssel com vetor resultante
	Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

	// remove míssil da cena se ele sair da área de jogo
	if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
	{
		GeoWars::audio->Volume(HITWALL, 0.7f);
		GeoWars::audio->Play(HITWALL);
		// adiciona explosão na cena
		//GeoWars::scene->Add(new WallHit(x, y), STATIC);
		GeoWars::scene->Add(new Light(x, y), STATIC);

		// remove míssil da cena
		GeoWars::scene->Delete();
	}
	anim->NextFrame();
}

// -------------------------------------------------------------------------------
