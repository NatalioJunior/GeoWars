
#include "SpawnerA.h"
#include "GeoWars.h"
#include "Blue.h"
#include "Hud.h"
#include "Soldier.h"
#include "EnemyHit.h"
#include "Explosion.h"
// ------------------------------------------------------------------------------

SpawnerA::SpawnerA(float posX, float posY, float angleSpawn, float scale) :  secs(9.0f, 14.0f)
{
	sprite = new Sprite("Resources/SpawnerA.png");
	// posi??o dos inimigos
	pX = posX;
	pY = posY;
	angle = angleSpawn;
	scaleF = scale;
	// atraso para a pr?xima onda 
	delay = secs.Rand();

	BBox(new Circle(70.0f));
	MoveTo(pX, pY);
	type = SPAWNER;

	GeoWars::nSpawners += 1;
}


// ------------------------------------------------------------------------------

SpawnerA::~SpawnerA()
{
	delete sprite;
}

// -------------------------------------------------------------------------------

void SpawnerA::Update()
{
	// contador de inimigos
	static uint counter = 1 + GeoWars::worldDifficulty;

	// se passou o tempo de atraso
	//if (timer.Elapsed(delay) && Hud::blues < 15)
	if (timer.Elapsed(delay))
	{
		if (counter > 0)
		{
			Vector speed = Vector(angle, 1);
			// toca som de nova onda
			//BasicAI::audio->Play(BLUE);

			// adiciona nova inimigo
			GeoWars::scene->Add(new Blue(x + (45 * cos(speed.Radians())), y - (45 * sin(speed.Radians())), GeoWars::player), MOVING);
			//GeoWars::scene->Add(new Soldier(pX+ 30, pY, GeoWars::player), MOVING);
			GeoWars::scene->Add(new Soldier(x + (100 * cos(speed.Radians())), y - (100 * sin(speed.Radians())), GeoWars::player), MOVING);

			delay = 1.05f;
			timer.Start();
			--counter;
		}
		else
		{
			// nova posi??o do inimigo
			//pX = posX.Rand();
			//pY = posY.Rand();

			// nova onda
			counter = 1 + GeoWars::worldDifficulty;
			delay = secs.Rand();
			timer.Start();
		}
	}
}

// -------------------------------------------------------------------------------
void SpawnerA::OnCollision(Object* obj) {
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

void SpawnerA::Draw()
{
	sprite->Draw(x, y, Layer::UPPER, scaleF * scale, 0, Color(1, 1, 1, 1));
}

// -------------------------------------------------------------------------------
