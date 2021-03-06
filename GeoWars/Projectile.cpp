
#include "WallHit.h"
#include "GeoWars.h"
#include "Light.h"
#include "Projectile.h"
// ------------------------------------------------------------------------------



Projectile::Projectile(float pX, float pY, float angle,float scale)
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
	speed.ScaleTo(3.0f);

	// move para posi??o
	MoveTo(pX + (45 * cos(speed.Radians())), pY - (45 * sin(speed.Radians())));

	//RotateTo(player->gun->speed->Angle() - 180.0f);
	RotateTo(-angle);

	// define tipo
	// define tipo
	type = ENMEY_PROJECTILE;
}

// ------------------------------------------------------------------------------

Projectile::~Projectile()
{
	delete sprite;
	delete tileset;
	delete anim;
}

// -------------------------------------------------------------------------------

void Projectile::Update()
{
	// move m?ssel com vetor resultante
	Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

	// remove m?ssil da cena se ele sair da ?rea de jogo
	if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
	{
		GeoWars::audio->Volume(HITWALL, 0.7f);
		GeoWars::audio->Play(HITWALL);
		// adiciona explos?o na cena
		//GeoWars::scene->Add(new WallHit(x, y), STATIC);
		GeoWars::scene->Add(new Light(x, y), STATIC);

		// remove m?ssil da cena
		GeoWars::scene->Delete();
	}
	anim->NextFrame();
}

// -------------------------------------------------------------------------------
