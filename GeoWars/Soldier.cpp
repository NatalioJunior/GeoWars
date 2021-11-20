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

// ---------------------------------------------------------------------------------

Soldier::Soldier(float pX, float pY, Player* p)
{
	player = p;
	sprite = new Sprite("Resources/Magenta.png");
	BBox(new Circle(18.0f));

	speed.RotateTo(0);
	speed.ScaleTo(1.0f);

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
	if (obj->Type() == MISSILE)
	{
		GeoWars::scene->Delete(this, MOVING);
		GeoWars::scene->Delete(obj, STATIC);
		GeoWars::scene->Add(new EnemyHit(x, y), STATIC);
		//GeoWars::scene->Delete(obj, STATIC);
		//GeoWars::scene->Delete(this, MOVING);
		//GeoWars::scene->Play(EXPLODE);
	}
	else {
		

		Point pA{ x,y };
		Point pB{ obj->X(),obj->Y() };

		float angleA = Line::Angle(pA, pB);
		float angleB = angleA + 180.0f;

		if (angleB > 360)
			angleB -= 360.0f;

		Vector impactA{ angleA, 0.1f * speed.Magnitude() };
		//Vector impactB{ angleB, 0.1f * obj->speed->Magnitude() };

		// adiciona vetor impacto à velocidade das rochas
		speed.Add(impactA);
		//greenB->speed.Add(impactA);

		if (speed.Magnitude() > 10.0f)
			speed.ScaleTo(10.0f);
	}
}

// -------------------------------------------------------------------------------

void Soldier::Update()
{
	// ajusta ângulo do vetor 
	speed.RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
	RotateTo(speed.Angle());
	//Rotate(200 * gameTime);
	if (Point::Distance(Point(x, y), Point(player->X(), player->Y())) > 200) {
		// movimenta objeto pelo seu vetor velocidade
		Translate(speed.XComponent() * 50.0f * gameTime, -speed.YComponent() * 50.0f * gameTime);
	}
	//if (Point::Distance(Point(x, y), Point(player->X(), player->Y())) < 1000) {
	//}
	if (timer.Elapsed() >= 9.0f) {

		GeoWars::scene->Add(new EnemyProjectile(x, y), STATIC);
		GeoWars::scene->Add(new Light(x + (45 * cos(speed.Radians())), y - (45 * sin(speed.Radians()))), STATIC);
		timer.Reset();
	}
}

// -------------------------------------------------------------------------------