/**********************************************************************************
// Orange (C�digo Fonte)
//
// Cria��o:     05 Ago 2019
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Objeto faz movimento retil�neo
//
**********************************************************************************/

#include "GeoWars.h"
#include "Orange.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Orange::Orange(float pX, float pY, float ang)
{
	sprite = new Sprite("Resources/Orange.png");
	speed = new Vector();
	speed->RotateTo(ang);
	speed->ScaleTo(400);
	BBox(new Circle(20.0f));

	RotateTo(-speed->Angle());

	// move para uma posi��o aleat�ria (canto superior esquerdo)
	RandF pos{ 100, 150 };
	//MoveTo(pos.Rand(), pos.Rand());
	MoveTo(pX, pY);

	multiplier = 70.0f;
	type = ORANGE;

	// configura��o do emissor de part�culas
	Generator emitter;
	emitter.imgFile = "Resources/Spark.png";    // arquivo de imagem
	emitter.angle = speed->Angle() + 180;       // �ngulo base do emissor
	emitter.spread = 10;                        // espalhamento em graus
	emitter.lifetime = 0.2f;                    // tempo de vida em segundos
	emitter.frequency = 0.010f;                 // tempo entre gera��o de novas part�culas
	emitter.percentToDim = 0.7f;                // desaparece ap�s 60% da vida
	emitter.minSpeed = 50.0f;                   // velocidade m�nima das part�culas
	emitter.maxSpeed = 100.0f;                  // velocidade m�xima das part�culas
	emitter.color.r = 1.0f;                     // componente Red da part�cula 
	emitter.color.g = 0.5;                      // componente Green da part�cula 
	emitter.color.b = 0.0f;                     // componente Blue da part�cula 
	emitter.color.a = 1.0f;                     // transpar�ncia da part�cula

	// cria sistema de part�culas
	tail = new Particles(emitter);
}

// ---------------------------------------------------------------------------------

Orange::~Orange()
{
	delete sprite;
	delete speed;
	delete tail;
}

// -------------------------------------------------------------------------------

void Orange::OnCollision(Object* obj)
{
	if (obj->Type() == MISSILE)
		GeoWars::scene->Delete(this, MOVING);
}

// -------------------------------------------------------------------------------

void Orange::Update()
{
	// movimenta objeto pelo seu vetor velocidade
	Translate(speed->XComponent() * gameTime, -speed->YComponent() * gameTime);

	// ajusta �ngulo do vetor na dire��o do jogador
	if (x < 50 || y < 50 || x > game->Width() - 50 || y > game->Height() - 50)
	{

		if (x < 50) {
			MoveTo(55, y);


			if (speed->Angle() == 135) {
				Rotate(-90);
				speed->Rotate(-90);
			}
			else if (speed->Angle() == 225) {
				Rotate(90);
				speed->Rotate(90);
			}

		}
		else if (x > game->Width() - 50) {
			MoveTo(game->Width() - 55, y);

			if (speed->Angle() == 45) {
				Rotate(90);
				speed->Rotate(90);
			}
			else if (speed->Angle() == 315) {
				Rotate(-90);
				speed->Rotate(-90);
			}

		}
		else if (y < 50) {
			MoveTo(x, 55);

			if (speed->Angle() == 45) {
				Rotate(-90);
				speed->Rotate(-90);
			}

			else if (speed->Angle() == 135) {
				Rotate(90);
				speed->Rotate(90);
			}

		}
		else if (y > game->Height() - 50) {

			MoveTo(x, game->Height() - 55);


			if (speed->Angle() == 225) {
				Rotate(-90);
				speed->Rotate(-90);
			}

			else if (speed->Angle() == 315) {
				Rotate(90);
				speed->Rotate(90);
			}

		}


		if (speed->Angle() == 0 || speed->Angle() == 90 || speed->Angle() == 180 || speed->Angle() == 270) {
			Rotate(180);
			speed->Rotate(180);
		}

		else {
			Rotate(180);
			speed->Rotate(180);


		}
		Translate(speed->XComponent() * gameTime, -speed->YComponent() * gameTime);
	}


	// atualiza calda da nave
	tail->Config().angle = speed->Angle();
	tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
	tail->Update(gameTime);
}

// ---------------------------------------------------------------------------------

void Orange::Draw()
{
	sprite->Draw(x, y, Layer::LOWER, scale, rotation);
	tail->Draw(Layer::LOWER, 1.0f);
}

// -------------------------------------------------------------------------------