#ifndef _GEOWARS_ENEMYPROJECTILE_H_
#define _GEOWARS_ENEMYPROJECTILE_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 
#include "TileSet.h"
#include "Animation.h"

// --------------------------------------------------------------------------------

class EnemyProjectile : public Object
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
	EnemyProjectile(float pX, float pY,float scale= 1.0f);                      // construtor
	~EnemyProjectile();                     // destrutor

	Vector& Speed();                // retona vetor velocidade
	void Update();                  // atualização
	void Draw();                    // desenho
};

// ------------------------------------------------------------------------------

inline Vector& EnemyProjectile::Speed()
{
	return speed;
}

inline void EnemyProjectile::Draw()
{
	//sprite->Draw(x, y, Layer::MIDDLE, scale, rotation);
	anim->Draw(x, y, Layer::MIDDLE, scale * EnemyProjectile::scaleF, rotation);
	
}

// ------------------------------------------------------------------------------

#endif