#include "EnemyProjectile.h"
#include "WallHit.h"
#include "GeoWars.h"
#include "Light.h"
// ------------------------------------------------------------------------------

Player*& EnemyProjectile::player = GeoWars::player;        // referência para o player

// ------------------------------------------------------------------------------

EnemyProjectile::EnemyProjectile(float pX, float pY, float scale)
{
	scaleF = scale;
	// inicializa sprite
	sprite = new Sprite("Resources/Bullet.png");
	tileset = new TileSet("Resources/plasmaball_pixelart.png",2,1);
	anim = new Animation(tileset, 0.5f, true);
	// cria bounding box
	BBox(new Circle(8*scaleF));

	// inicializa velocidade

   // speed.RotateTo(-player->gun->speed->Angle() - 180.0f);
	speed.RotateTo(Line::Angle(Point(pX, pY), Point(player->X(), player->Y())));
	speed.ScaleTo(3.0f);

	// move para posição
	MoveTo(pX + (45 * cos(speed.Radians())), pY - (45 * sin(speed.Radians())));

	//RotateTo(player->gun->speed->Angle() - 180.0f);
	RotateTo(-Line::Angle(Point(pX, pY), Point(player->X(), player->Y())));

	// define tipo
	type = ENMEY_PROJECTILE;
}

// ------------------------------------------------------------------------------

EnemyProjectile::~EnemyProjectile()
{
	delete sprite;
	delete tileset;
	delete anim;
}

// -------------------------------------------------------------------------------

void EnemyProjectile::Update()
{
	// move míssel com vetor resultante
	Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

	// remove míssil da cena se ele sair da área de jogo
	if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
	{
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
