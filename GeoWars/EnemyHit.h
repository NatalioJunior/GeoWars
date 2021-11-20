
#ifndef _GEOWARS_ENEMYHIT_H_
#define _GEOWARS_ENEMYHIT_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Particles.h"
#include "Missile.h"

// ---------------------------------------------------------------------------------

class EnemyHit : public Object
{
private:
	Particles* particle1;                 // sistema de partículas
	Particles* particle2;                 // sistema de partículas

public:
	EnemyHit(float pX, float pY);        // construtor
	~EnemyHit();                         // destrutor

	int  Size();                        // quantidade de partículas
	void Update();                      // atualização
	void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------

inline int EnemyHit::Size()
{
	return particle1->Size();
	return particle2->Size();
}

inline void EnemyHit::Draw()
{
	particle1->Draw(Layer::MIDDLE, 0.0f);
	particle2->Draw(Layer::MIDDLE, 0.0f);
}

// ---------------------------------------------------------------------------------


#endif