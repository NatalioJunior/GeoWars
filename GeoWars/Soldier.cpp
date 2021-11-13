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

// ---------------------------------------------------------------------------------

Soldier::Soldier(float pX, float pY, Player* p)
{
	player = p;
	sprite = new Sprite("Resources/Magenta.png");
	BBox(new Circle(18.0f));

	speed.RotateTo(0);
	speed.ScaleTo(2.0f);

	MoveTo(pX, pY);
	type = SOLDIER;

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
		GeoWars::scene->Delete(obj, STATIC);
		GeoWars::scene->Delete(this, MOVING);
		//GeoWars::scene->Play(EXPLODE);
	}
}

// -------------------------------------------------------------------------------

void Soldier::Update()
{
	// ajusta ângulo do vetor 
	if (Point::Distance(Point(x, y), Point(player->X(), player->Y())) < 1000) {
		speed.RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
		RotateTo(speed.Angle());
		//Rotate(200 * gameTime);
		if (Point::Distance(Point(x, y), Point(player->X(), player->Y())) < 900 && Point::Distance(Point(x, y), Point(player->X(), player->Y())) > 200) {
			// movimenta objeto pelo seu vetor velocidade
			Translate(speed.XComponent() * 50.0f * gameTime, -speed.YComponent() * 50.0f * gameTime);
		}
	}
}

// -------------------------------------------------------------------------------