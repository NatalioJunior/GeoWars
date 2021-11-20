
#include "SpawnerBase.h"
#include "GeoWars.h"
#include "Blue.h"
#include "Hud.h"
#include "Soldier.h"

// ------------------------------------------------------------------------------

SpawnerBase::SpawnerBase() : posX(50, window->Width() - 50), posY(50, window->Height() - 50), secs(8.0f, 12.0f)
{
	sprite = new Sprite("Resources/Player.png");
	// posição dos inimigos
	pX = posX.Rand();
	pY = posY.Rand();

	// atraso para a próxima onda 
	delay = secs.Rand();
	Point vertex[4] =
	{
		Point(-75.0f,-70.0f), Point(75.0f,-70.0f), Point(75.0f,70.0f), Point(-75.0f, 70.0f)
	};
	BBox(new Poly(vertex, 4));
	MoveTo(pX, pY);
	type = SPAWNER;
}


// ------------------------------------------------------------------------------

SpawnerBase::~SpawnerBase()
{
	delete sprite;
}

// -------------------------------------------------------------------------------

void SpawnerBase::Update()
{
	// contador de inimigos
	static uint counter = 8;

	// se passou o tempo de atraso
	//if (timer.Elapsed(delay) && Hud::blues < 15)
	if (timer.Elapsed(delay))
	{
		if (counter > 0)
		{
			// toca som de nova onda
			//BasicAI::audio->Play(BLUE);

			// adiciona nova inimigo
			GeoWars::scene->Add(new Blue(pX, pY, GeoWars::player), MOVING);
			GeoWars::scene->Add(new Soldier(pX, pY, GeoWars::player), MOVING);

			delay = 0.850f;
			timer.Start();
			--counter;
		}
		else
		{
			// nova posição do inimigo
			pX = posX.Rand();
			pY = posY.Rand();

			// nova onda
			counter = 8;
			delay = secs.Rand();
			timer.Start();
		}
	}
}

// -------------------------------------------------------------------------------
void SpawnerBase::OnCollision(Object* obj) {
	if (obj->Type() == MISSILE) {
		GeoWars::scene->Delete(obj, STATIC);
		currentLife -= 10;
		if (currentLife <= 0) {
			GeoWars::scene->Delete(this, MOVING);
		}
	}
}
// -------------------------------------------------------------------------------

void SpawnerBase::Draw()
{
	sprite->Draw(x, y, Layer::UPPER, 2, 0, Color(1, 1, 1, 1));
}

// -------------------------------------------------------------------------------
