#include "EnemyProjectile.h"
#include "WallHit.h"
#include "GeoWars.h"
#include "Light.h"
// ------------------------------------------------------------------------------

Player*& EnemyProjectile::player = GeoWars::player;        // refer�ncia para o player

// ------------------------------------------------------------------------------

EnemyProjectile::EnemyProjectile(float pX, float pY)
{
	// inicializa sprite
	sprite = new Sprite("Resources/Bullet.png");

	// cria bounding box
	BBox(new Circle(8));

	// inicializa velocidade

   // speed.RotateTo(-player->gun->speed->Angle() - 180.0f);
	speed.RotateTo(Line::Angle(Point(pX, pY), Point(player->X(), player->Y())));
	speed.ScaleTo(15.0f);

	// move para posi��o
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
}

// -------------------------------------------------------------------------------

void EnemyProjectile::Update()
{
	// move m�ssel com vetor resultante
	Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

	// remove m�ssil da cena se ele sair da �rea de jogo
	if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
	{
		GeoWars::audio->Volume(HITWALL, 0.7f);
		GeoWars::audio->Play(HITWALL);
		// adiciona explos�o na cena
		GeoWars::scene->Add(new WallHit(x, y), STATIC);
		GeoWars::scene->Add(new Light(x, y), STATIC);

		// remove m�ssil da cena
		GeoWars::scene->Delete();
	}
}

// -------------------------------------------------------------------------------
