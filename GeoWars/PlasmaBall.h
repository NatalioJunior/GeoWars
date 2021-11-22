#ifndef _PLATANK_PLASMABALL_H_
#define _PLATANK_PLASMABALL_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 
#include "TileSet.h"
#include "Animation.h"

// --------------------------------------------------------------------------------

class PlasmaBall : public Object
{
private:
	const float MaxDistance = 4406; // distância máxima para o jogador
	const float BaseVolume = 0.8f;  // volume base para explosão

	static Player*& player;        // referência para o player
	Sprite* sprite;                // sprite do míssil
	TileSet* tileset;
	Animation* anim;
	Vector speed;                   // velocidade do míssil    
	float scaleF;
public:
	PlasmaBall(float pX, float pY, float angle, float scale = 1.0f);                      // construtor
	~PlasmaBall();                     // destrutor

	Vector& Speed();                // retona vetor velocidade
	void Update();                  // atualização
	void Draw();                    // desenho
};

// ------------------------------------------------------------------------------

inline Vector& PlasmaBall::Speed()
{
	return speed;
}

inline void PlasmaBall::Draw()
{
	//sprite->Draw(x, y, Layer::MIDDLE, scale, rotation);
	anim->Draw(x, y, Layer::MIDDLE, scale * PlasmaBall::scaleF, rotation);

}

// ------------------------------------------------------------------------------

#endif