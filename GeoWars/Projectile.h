#ifndef _GEOWARS_PROJECTILE_H_
#define _GEOWARS_PROJECTILE_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 
#include "TileSet.h"
#include "Animation.h"

// --------------------------------------------------------------------------------

class Projectile : public Object
{
private:
	const float MaxDistance = 4406; // dist�ncia m�xima para o jogador
	const float BaseVolume = 0.8f;  // volume base para explos�o

	static Player*& player;        // refer�ncia para o player
	Sprite* sprite;                // sprite do m�ssil
	TileSet* tileset;
	Animation* anim;
	Vector speed;                   // velocidade do m�ssil    
	float scaleF;
public:
	Projectile(float pX, float pY,float angle, float scale = 1.0f);                      // construtor
	~Projectile();                     // destrutor

	Vector& Speed();                // retona vetor velocidade
	void Update();                  // atualiza��o
	void Draw();                    // desenho
};

// ------------------------------------------------------------------------------

inline Vector& Projectile::Speed()
{
	return speed;
}

inline void Projectile::Draw()
{
	//sprite->Draw(x, y, Layer::MIDDLE, scale, rotation);
	anim->Draw(x, y, Layer::MIDDLE, scale * Projectile::scaleF, rotation);

}

// ------------------------------------------------------------------------------

#endif