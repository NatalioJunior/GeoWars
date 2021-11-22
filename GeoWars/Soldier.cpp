/**********************************************************************************
// Magenta (Código Fonte)
//
// Criação:     10 Out 2012
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz um perseguição direta
//
**********************************************************************************/

#include "GeoWars.h"
#include "Soldier.h"
#include "Random.h" 
#include "Hud.h"
#include "Light.h"
#include "EnemyProjectile.h"
#include "EnemyHit.h"
#include "Itens.h"

// ---------------------------------------------------------------------------------

Soldier::Soldier(float pX, float pY, Player* p) : weapon(0.0f,1.0f)
{
	player = p;
	sprite = new Sprite("Resources/Magenta.png");
	speed = new Vector(0, 2.0f);
	BBox(new Circle(18.0f));

	MoveTo(pX, pY);
	type = SOLDIER;

	timer.Start();

	//inicia contador de sodlados
	GeoWars::nSoldier += 1;
}
// ---------------------------------------------------------------------------------

Soldier::~Soldier()
{
	delete sprite;
}

// -------------------------------------------------------------------------------

void Soldier::OnCollision(Object* obj)
{
	if (obj->Type() == MISSILE)
	{
		if (weapon.Rand() < 0.25f) {
			GeoWars::scene->Add(new Itens(HEAVY, x, y), STATIC);
		}
		GeoWars::player->score += 5;
		GeoWars::scene->Delete(obj, STATIC);
		GeoWars::scene->Add(new EnemyHit(x, y), STATIC);
		GeoWars::nSoldier -= 1;
		GeoWars::scene->Delete(this, MOVING);
	}
	else if (obj->Type() == PLAYER) {
		GeoWars::scene->Delete(this, MOVING);
		GeoWars::scene->Add(new EnemyHit(x, y), STATIC);
		GeoWars::nSoldier -= 1;
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
	// ajusta ângulo do vetor 
	float angle = Line::Angle(Point(x, y), Point(player->X(), player->Y()));
	float magnitude = 2.0f * gameTime;

	Vector target = Vector(angle, magnitude);

	speed->Add(target);

	if (speed->Magnitude() > 4.0f)
		speed->ScaleTo(4.0f);

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