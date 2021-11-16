/**********************************************************************************
// Orange (Código Fonte)
//
// Criação:     05 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz movimento retilíneo
//
**********************************************************************************/

#include "GeoWars.h"
#include "Orange.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Orange::Orange(float pX, float pY, float ang)
{
	tileset = new TileSet("Resources/Missile.png", 1, 5);
	anim = new Animation(tileset, 0.250f, true);
	speed = new Vector();
	speed->RotateTo(ang);
	speed->ScaleTo(400);
	BBox(new Circle(20.0f));

	RotateTo(-speed->Angle());

	// move para uma posição aleatória (canto superior esquerdo)
	RandF pos{ 100, 150 };
	//MoveTo(pos.Rand(), pos.Rand());
	MoveTo(pX, pY);

	multiplier = 70.0f;
	type = ORANGE;

	// configuração do emissor de partículas
	Generator emitter;
	emitter.imgFile = "Resources/Spark.png";    // arquivo de imagem
	emitter.angle = speed->Angle() + 180;       // ângulo base do emissor
	emitter.spread = 20;                        // espalhamento em graus
	emitter.lifetime = 0.2f;                    // tempo de vida em segundos
	emitter.frequency = 0.010f;                 // tempo entre geração de novas partículas
	emitter.percentToDim = 0.7f;                // desaparece após 60% da vida
	emitter.minSpeed = 60.0f;                   // velocidade mínima das partículas
	emitter.maxSpeed = 60.0f;                  // velocidade máxima das partículas
	emitter.color.r = 1.0f;                     // componente Red da partícula 
	emitter.color.g = 0.5;                      // componente Green da partícula 
	emitter.color.b = 0.0f;                     // componente Blue da partícula 
	emitter.color.a = 1.0f;                     // transparência da partícula

	// cria sistema de partículas
	tail = new Particles(emitter);
}

// ---------------------------------------------------------------------------------

Orange::~Orange()
{
	delete tileset;
	delete anim;
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

	// ajusta ângulo do vetor na direção do jogador
	if (x < 50 || y < 50 || x > game->Width() - 50 || y > game->Height() - 50)
	{

		if (x < 75) {
			MoveTo(80, y);


			if (speed->Angle() == 135) {
				Rotate(-90);
				speed->Rotate(-90);
			}
			else if (speed->Angle() == 225) {
				Rotate(90);
				speed->Rotate(90);
			}

		}
		else if (x > game->Width() - 75) {
			MoveTo(game->Width() - 80, y);

			if (speed->Angle() == 45) {
				Rotate(90);
				speed->Rotate(90);
			}
			else if (speed->Angle() == 315) {
				Rotate(-90);
				speed->Rotate(-90);
			}

		}
		else if (y < 75) {
			MoveTo(x, 80);

			if (speed->Angle() == 45) {
				Rotate(-90);
				speed->Rotate(-90);
			}

			else if (speed->Angle() == 135) {
				Rotate(90);
				speed->Rotate(90);
			}

		}
		else if (y > game->Height() - 75) {

			MoveTo(x, game->Height() - 80);


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
	tail->Generate(x - 45 * cos(speed->Radians()), y + 45 * sin(speed->Radians()));
	tail->Update(gameTime);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void Orange::Draw()
{
	anim->Draw(x, y, Layer::LOWER, scale, rotation - 90.0f);
	tail->Draw(Layer::LOWER, 1.0f);
}

// -------------------------------------------------------------------------------