
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
	Particles* particle1;                 // sistema de part�culas
	Particles* particle2;                 // sistema de part�culas

public:
	EnemyHit(float pX, float pY);        // construtor
	~EnemyHit();                         // destrutor

	int  Size();                        // quantidade de part�culas
	void Update();                      // atualiza��o
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