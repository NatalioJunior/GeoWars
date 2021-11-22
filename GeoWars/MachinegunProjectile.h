#ifndef _PLATANK_MACHINEGUNPROJECTILE_H_
#define _PLATANK_MACHINEGUNPROJECTILE_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 
#include "TileSet.h"
#include "Animation.h"

// --------------------------------------------------------------------------------

class MachineGunProjectile : public Object
{
private:
	const float MaxDistance = 4406; // distância máxima para o jogador
	const float BaseVolume = 0.8f;  // volume base para explosão

	static Player*& player;        // referência para o player
	
	TileSet* tileset;
	Animation* anim;
	Vector speed;                   // velocidade do míssil    
	float scaleF;
public:
	MachineGunProjectile(float pX, float pY, float angle, float scale = 1.0f);                      // construtor
	~MachineGunProjectile();                     // destrutor

	Vector& Speed();                // retona vetor velocidade
	void Update();                  // atualização
	void Draw();                    // desenho
};

// ------------------------------------------------------------------------------

inline Vector& MachineGunProjectile::Speed()
{
	return speed;
}

inline void MachineGunProjectile::Draw()
{
	//sprite->Draw(x, y, Layer::MIDDLE, scale, rotation);
	anim->Draw(x, y, Layer::MIDDLE, scale * MachineGunProjectile::scaleF, rotation,Color(1,1,0,1));

}

// ------------------------------------------------------------------------------

#endif