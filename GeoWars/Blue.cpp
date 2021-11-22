/**********************************************************************************
// Blue (Código Fonte)
//
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz uma perseguição suavizada
//
**********************************************************************************/

#include "GeoWars.h"
#include "Blue.h"
#include "Random.h" 
#include "EnemyHit.h"
#include "EnemyProjectile.h"
#include "Light.h"
// ---------------------------------------------------------------------------------

Blue::Blue(float pX, float pY, Player* p)
{
	player = p;
	sprite = new Sprite("Resources/Magenta.png");
	speed = new Vector(0, 2.0f);
	BBox(new Circle(20.0f));

	// move para uma posição aleatória (canto superior direito)
	RandF posX{ game->Width() - 400, game->Width() - 300 };
	RandF posY{ 300, 400 };
	//MoveTo(posX.Rand(), posY.Rand());
	MoveTo(pX, pY);

	factor = -0.25f;
	type = BLUE;

	timer.Start();

	GeoWars::nBlue += 1;
}

// ---------------------------------------------------------------------------------

Blue::~Blue()
{
	delete sprite;
	delete speed;
}

// -------------------------------------------------------------------------------

void Blue::OnCollision(Object* obj)
{
	if (obj->Type() == MISSILE) {
		GeoWars::player->score += 10;
		GeoWars::scene->Delete(this, MOVING);
		GeoWars::scene->Delete(obj, STATIC);
		GeoWars::scene->Add(new EnemyHit(x, y), STATIC);
		GeoWars::nBlue -= 1;
	}
	else if (obj->Type() == PLAYER) {
		GeoWars::scene->Delete(this, MOVING);
		GeoWars::scene->Add(new EnemyHit(x, y), STATIC);
		GeoWars::nBlue -= 1;
	}
	if (obj->Type() == BLUE || obj->Type() == SOLDIER || obj->Type() == SPAWNER) {
		Vector target = Vector(Line::Angle(Point(x, y), Point(obj->X(), obj->Y())), 120.0f * gameTime);
		target.Rotate(180.0f);
		speed->Add(target);
	}

}

// -------------------------------------------------------------------------------

void Blue::Update()
{
	// a magnitude do vetor 'target' controla quão 
	// rápido o objeto converge para a direção do alvo
	float angle = Line::Angle(Point(x, y), Point(player->X(), player->Y()));
	float magnitude = 2.0f * gameTime;
	Vector target = Vector(angle, magnitude);

	// ajusta velocidade atual na direção do alvo
	speed->Add(target);

	// limita a magnitude da velocidade para impedir 
	// que ela cresça indefinidamente pelo soma vetorial
	if (speed->Magnitude() > 3.5f)
		speed->ScaleTo(3.5f);

	// move o objeto pelo seu vetor velocidade
	//Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);

	//RotateTo(speed->Angle() +90);
	//rotation = speed->Angle();
	//Rotate(200 * gameTime);
	if (Point::Distance(Point(x, y), Point(player->X(), player->Y())) > 200) {
		// movimenta objeto pelo seu vetor velocidade
		Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);
	}

	// aplica fator de escala
	Scale(1.0f + factor * gameTime);

	// amplia e reduz objeto
	if (scale < 0.85f)
		factor = 0.25f;
	if (scale > 1.00f)
		factor = -0.25f;

	// mantém o objeto dentro do mundo do jogo
	if (x < 50)
		MoveTo(50, y);
	if (y < 50)
		MoveTo(x, 50);
	if (x > game->Width() - 50)
		MoveTo(game->Width() - 50, y);
	if (y > game->Height() - 50)
		MoveTo(x, game->Height() - 50);

	if (timer.Elapsed() >= 8.0f) {

		GeoWars::scene->Add(new EnemyProjectile(x, y), STATIC);
		GeoWars::scene->Add(new Light(x + (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians()))), STATIC);
		timer.Reset();
	}
}
void Blue::Draw()
{
	sprite->Draw(x, y, Layer::LOWER, .2f * scale, -Line::Angle(Point(x, y), Point(player->X(), player->Y())), Color(0.5f, 0.5f, 1.0f, 1.0f));
}


// -------------------------------------------------------------------------------