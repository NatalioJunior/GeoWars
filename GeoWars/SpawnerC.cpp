
#include "SpawnerC.h"
#include "GeoWars.h"
#include "Magenta.h"
#include "Hud.h"
#include "EnemyHit.h"
#include "Explosion.h"
// ------------------------------------------------------------------------------

SpawnerC::SpawnerC(float poX, float poY, float angleSpawn, float scale) :secs(2.0f, 4.0f)
{
	sprite = new Sprite("Resources/SpawnerD.png");
	// posição dos inimigos
	pX = poX;
	pY = poY;
	angle = angleSpawn;
	scaleF = scale;

	// atraso para a próxima onda 
	delay = secs.Rand();
	BBox(new Rect(-75.0f, -70.0f, 75.0f, 70.0f));
	MoveTo(pX, pY);
	type = SPAWNER;

	GeoWars::nSpawners += 1;
}

// ------------------------------------------------------------------------------

SpawnerC::~SpawnerC()
{
	delete sprite;
}

// -------------------------------------------------------------------------------

void SpawnerC::Update()
{
	// se passou o tempo de atraso
	/*if (timer.Elapsed(delay))
	{

		// adiciona novo inimigo

		Vector speed = Vector(angle, 1);


		// reinicia o timer
		timer.Start();
	}*/
	// contador de inimigos
	static uint counter = 1 + GeoWars::worldDifficulty;

	// se passou o tempo de atraso
	if (timer.Elapsed(delay))
	{
		if (counter > 0)
		{

			Vector speed = Vector(angle, 1);

			GeoWars::scene->Add(new Magenta(x + (45 * cos(speed.Radians())), y - (45 * sin(speed.Radians())), GeoWars::player), MOVING);

			delay = 0.450f;
			timer.Start();
			--counter;
		}
		else
		{
			// nova onda
			counter = 1 + GeoWars::worldDifficulty;
			delay = secs.Rand();
			timer.Start();
		}
	}
}
void SpawnerC::OnCollision(Object* obj) {
	if (obj->Type() == MISSILE) {
		GeoWars::scene->Add(new EnemyHit(obj->X(), obj->Y()), STATIC);
		GeoWars::audio->Play(HITWALL);
		GeoWars::scene->Delete(obj, STATIC);
		currentLife -= 10;
		if (currentLife <= 0) {
			GeoWars::player->score += 300;
			Vector speed = Vector(angle, 1);
			GeoWars::scene->Add(new Explosion(x - 10 + (130 * cos(speed.Radians())), y - 14 - (130 * sin(speed.Radians()))), STATIC);
			GeoWars::scene->Add(new Explosion(x + 10, y), STATIC);
			GeoWars::scene->Add(new Explosion(x - 24, y), STATIC);
			GeoWars::scene->Add(new Explosion(x + (40 * cos(speed.Radians())), 14 + y - (15 * sin(speed.Radians()))), STATIC);
			GeoWars::scene->Delete(this, MOVING);
			GeoWars::nSpawners -= 1;
		}
	}
}
// -------------------------------------------------------------------------------

void SpawnerC::Draw()
{
	sprite->Draw(x, y, Layer::LOWER, scaleF * scale, 0, Color(1, 1, 1, 1));
}

// -------------------------------------------------------------------------------
