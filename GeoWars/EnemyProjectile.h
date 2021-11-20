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
	const float MaxDistance = 4406; // dist�ncia m�xima para o jogador
	const float BaseVolume = 0.8f;  // volume base para explos�o

	static Player*& player;        // refer�ncia para o player
	Sprite* sprite;                // sprite do m�ssil
	TileSet* tileset;
	Animation* anim;
	Vector speed;                   // velocidade do m�ssil    

public:
	EnemyProjectile(float pX, float pY);                      // construtor
	~EnemyProjectile();                     // destrutor

	Vector& Speed();                // retona vetor velocidade
	void Update();                  // atualiza��o
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
	anim->Draw(x, y, Layer::MIDDLE, scale, rotation);
	
}

// ------------------------------------------------------------------------------

#endif