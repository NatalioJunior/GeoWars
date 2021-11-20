/**********************************************************************************
// Alien (Código Fonte)
//
// Criação:     25 Mar 2013
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Executa scripts com padrões de movimentação
//
**********************************************************************************/

#include "MiniBossLarryTank.h"

#include "GeoWars.h"
#include <cmath>
#include "Explosion.h"

// ---------------------------------------------------------------------------------

MiniBossLarryTank::MiniBossLarryTank(Instruction* vet, int tam, float pX, float pY)
	: angle(-8, 8), magnitude(1, 8)
{

	sprite = new Sprite("Resources/Player.png");
	speed = new Vector(90.0f, 0.0f);
	// tipo do alien
	type = MINI_BOSS;

	// faz cópia do script 
	script = new Instruction[tam];
	for (int i = 0; i < tam; i++)
		script[i] = vet[i];

	// carrega tileset do objeto

	//anim = new Animation(alienSet, 0.500, true);
	Point vertex[4] =
	{
		Point(-37.5f,-35.0f), Point(37.5f,-35.0f), Point(37.5f,35.0f), Point(-37.0f, 35.0f)
	};
	BBox(new Poly(vertex, 4));
	MoveTo(pX, pY);
	//speed = { 0.0f, 0.0f };

	// inicia execução do script
	index = 0;
	end = tam - 1;
	duration = script[index].duration;
	timer.Start();


}

// ---------------------------------------------------------------------------------

MiniBossLarryTank::~MiniBossLarryTank()
{
	delete[] script;
	//delete alienSet;
	//delete anim;
	delete speed;
	delete sprite;

}

// ---------------------------------------------------------------------------------

void MiniBossLarryTank::OnCollision(Object* obj)
{
	if (obj->Type() == MISSILE) {
		GeoWars::scene->Delete(obj, STATIC);
		currentLife -= 10;
		if (currentLife <= 0) {
			GeoWars::scene->Add(new Explosion(x,y),STATIC);
			GeoWars::scene->Delete(this, MOVING);
		}
	}
}

// -------------------------------------------------------------------------------

void MiniBossLarryTank::Update()
{
	// deslocamento padrão
	float delta = 50 * gameTime;

	// atualiza animações
	//anim->NextFrame();

	// ----------------------------
	// Próxima instrução do script
	// ----------------------------

	if (script[index].instruction == MOVETO || script[index].instruction == SLIDETO)
	{
		// pega posição X e Y de destino
		float targetX = script[index].angle;
		float targetY = script[index].magnitude;

		// se chegou bem próximo do destino
		if (abs(x - targetX) < 2 && abs(y - targetY) < 2)
		{
			// move exatamente para a posição de destino
			MoveTo(targetX, targetY);

			// passa para a próxima instrução
			index = (index == end ? index : ++index);
			duration = script[index].duration;
			timer.Start();
		}
	}
	else
	{
		// se esgotou o tempo da instrução
		if (timer.Elapsed(duration))
		{
			// passa para a próxima instrução
			index = (index == end ? index : ++index);
			duration = script[index].duration;
			timer.Start();
		}
	}

	// ------------------------
	// Interpretador do script
	// ------------------------

	// realiza salto antes de qualquer outra instrução
	if (script[index].instruction == JUMP)
	{
		index = int(script[index].angle);
		duration = script[index].duration;
		timer.Start();
	}

	switch (script[index].instruction)
	{
	case MOVE:    // MOVE | Ângulo | Magnitude | Duração
		speed->RotateTo(script[index].angle);
		speed->ScaleTo(script[index].magnitude);
		RotateTo(-speed->Angle() + 90);
		break;

	case MOVETO:  // MOVETO | PosX | PosY | Magnitude
		speed->RotateTo(Line::Angle(Point(x, y), Point(script[index].angle, script[index].magnitude)));
		speed->ScaleTo(script[index].duration);
		RotateTo(-speed->Angle() + 90);
		break;

	case SLIDE:   // SLIDE | Ângulo | Magnitude | Duração
		speed->RotateTo(script[index].angle);
		speed->ScaleTo(script[index].magnitude);
		break;

	case SLIDETO: // SLIDETO | PosX | PosY | Magnitude
		speed->RotateTo(Line::Angle(Point(x, y), Point(script[index].angle, script[index].magnitude)));
		speed->ScaleTo(script[index].duration);
		break;

	case TURN:    // TURN | Ângulo | Magnitude | Duração
	{
		Vector target{ script[index].angle, script[index].magnitude * delta };
		speed->Add(target);
		RotateTo(-speed->Angle() + 90);
		break;
	}
	case ROTATE:  // ROTATE | Ângulo | Magnitude | Duração
		speed->Rotate(-script[index].angle * delta);
		speed->ScaleTo(script[index].magnitude);
		Rotate(-script[index].angle * delta);
		break;

	case RANDOM:  // RANDOM | Ângulo | Magnitude | Duração
		speed->Rotate(-angle.Rand());
		speed->ScaleTo(magnitude.Rand());
		RotateTo(-speed->Angle() + 90);
		break;
	}

	// desloca objeto pelo seu vetor velocidade
	Translate(speed->XComponent() * delta, -speed->YComponent() * delta);
}
void MiniBossLarryTank::Draw()
{
	sprite->Draw(x, y, Layer::UPPER, 1.0f, -speed->Angle() + 90.0f, Color(0.6f, 1.0f, 0.6f, 1.0f));
	//tail->Draw(Layer::LOWER);
}

// -------------------------------------------------------------------------------