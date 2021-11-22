/**********************************************************************************
// Magenta (C�digo Fonte)
//
// Cria��o:     10 Out 2012
// Atualiza��o: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Objeto faz um persegui��o direta
//
**********************************************************************************/

#include "GeoWars.h"
#include "Soldier.h"
#include "Random.h" 
#include "Hud.h"
#include "Light.h"
#include "EnemyProjectile.h"
#include "EnemyHit.h"

// ---------------------------------------------------------------------------------

Soldier::Soldier(float pX, float pY, Player* p)
{
	player = p;
	sprite = new Sprite("Resources/Magenta.png");
	speed = new Vector(0, 2.0f);
	BBox(new Circle(18.0f));

	MoveTo(pX, pY);
	type = SOLDIER;

	timer.Start();
}
// ---------------------------------------------------------------------------------

Soldier::~Soldier()
{
	delete sprite;
}

// -------------------------------------------------------------------------------

void Soldier::OnCollision(Object* obj)
{
	if (obj->Type() == MISSILE )
	{
		GeoWars::scene->Delete(obj, STATIC);
		GeoWars::scene->Delete(this, MOVING);
		GeoWars::scene->Add(new EnemyHit(x, y), STATIC);	
		//GeoWars::scene->Delete(obj, STATIC);
		//GeoWars::scene->Delete(this, MOVING);
		//GeoWars::scene->Play(EXPLODE);
	}
	else if (obj->Type() == PLAYER) {
		GeoWars::scene->Delete(this, MOVING);
		GeoWars::scene->Add(new EnemyHit(x, y), STATIC);

	}
	if (obj->Type() == SOLDIER || obj->Type() == BLUE || obj->Type() == SPAWNER) {
		Vector target = Vector(Line::Angle(Point(x, y), Point(obj->X(), obj->Y())), 120.0f * gameTime);
		target.Rotate(180.0f);
		speed->Add(target);
	}
}

// -------------------------------------------------------------------------------

void Soldier::Update()
{
	// ajusta �ngulo do vetor 
	float angle = Line::Angle(Point(x, y), Point(player->X(), player->Y()));
	float magnitude = 2.0f * gameTime;

	Vector target = Vector(angle, magnitude);

	speed->Add(target);

	if (speed->Magnitude() > 2.5f)
		speed->ScaleTo(2.5f);

	if (Point::Distance(Point(x, y), Point(player->X(), player->Y())) > 200) {
		// movimenta objeto pelo seu vetor velocidade
		Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);
	}

	if (timer.Elapsed() >= 9.0f) {

		GeoWars::scene->Add(new EnemyProjectile(x, y), STATIC);
		GeoWars::scene->Add(new Light(x + (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians()))), STATIC);
		timer.Reset();
	}
}

// -------------------------------------------------------------------------------