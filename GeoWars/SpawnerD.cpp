#include "SpawnerD.h"
#include "GeoWars.h"
#include "Orange.h"
#include "Hud.h"
#include "EnemyHit.h"
#include "Explosion.h"
// ------------------------------------------------------------------------------

SpawnerD::SpawnerD(float poX, float poY, float angleSpawn, float scale) : position(0, 3), delay(1.0f, 5.0f)
{
	// número de inimigos na horizontal (X) e na vertical (Y)
	numX = 8;
	numY = 8;

	// posição dos inimigos
	posX = 0;
	posY = 0;
	pX = poX;
	pY = poY;

	angle = angleSpawn;
	scaleF = scale;
	sprite = new Sprite("Resources/SpawnerD.png");
	BBox(new Circle(70.0f));
	MoveTo(pX, pY);
	// não enviar nova onda agora
	newWave = true;
	waveDelay = delay.Rand();

	type = SPAWNER;
}

// ------------------------------------------------------------------------------

SpawnerD::~SpawnerD()
{
	delete sprite;
}
void SpawnerD::OnCollision(Object* obj) {
	if (obj->Type() == MISSILE) {
		GeoWars::scene->Add(new EnemyHit(obj->X(), obj->Y()), STATIC);
		GeoWars::audio->Play(HITWALL);
		GeoWars::scene->Delete(obj, STATIC);
		currentLife -= 10;
		if (currentLife <= 0) {
			Vector speed = Vector(angle, 1);
			GeoWars::scene->Add(new Explosion(x - 10 + (130 * cos(speed.Radians())), y - 14 - (130 * sin(speed.Radians()))), STATIC);
			GeoWars::scene->Add(new Explosion(x + 10, y), STATIC);
			GeoWars::scene->Add(new Explosion(x - 24, y), STATIC);
			GeoWars::scene->Add(new Explosion(x + (40 * cos(speed.Radians())), 14 + y - (15 * sin(speed.Radians()))), STATIC);
			GeoWars::scene->Delete(this, MOVING);

		}
	}
}
// -------------------------------------------------------------------------------

void SpawnerD::Update()
{
	// nova onda foi solicitada
	if (newWave)
	{
		// se passou o tempo de atraso da solicitação
		if (timer.Elapsed(waveDelay))
		{
			// toca som de nova onda
			GeoWars::audio->Play(ORANGE);

			// origem da onda é aleatória
			switch (position.Rand())
			{
			case 0:
				// lado esquerdo da tela
				posY = 100;
				for (int i = 0; i < numY; ++i)
				{
					GeoWars::scene->Add(new Orange(50, posY, 0), MOVING);
					posY += 50;
				}
				break;
			case 1:
				// lado superior da tela
				posX = 100;
				for (int i = 0; i < numX; ++i)
				{
					GeoWars::scene->Add(new Orange(posX, 50, 270), MOVING);
					posX += 50;
				}
				break;
			case 2:
				// lado direito da tela
				posY = game->Height() - 100;
				for (int i = 0; i < numY; ++i)
				{
					GeoWars::scene->Add(new Orange(game->Width() - 50, posY, 180), MOVING);
					posY -= 50;
				}
				break;
			case 3:
				// lado inferior da tela
				posX = game->Width() - 100;
				for (int i = 0; i < numX; ++i)
				{
					GeoWars::scene->Add(new Orange(posX, game->Height() - 50, 90), MOVING);
					posX -= 50;
				}
				break;
			}

			// onda enviada
			newWave = false;
		}
	}
	else
	{
		// solicita nova onda se existirem poucos inimigos
	   /*
		if (Hud::oranges < 10)
		{
			waveDelay = delay.Rand();
			timer.Start();
			newWave = true;
		}
	   */
	}
}

// -------------------------------------------------------------------------------


void SpawnerD::Draw()
{
	sprite->Draw(x, y, Layer::LOWER, scaleF * scale, 0.0f, Color(1.0f, 0.66f, 0.0f, 1.0f));
}

// -------------------------------------------------------------------------------
