
#ifndef _GEOWARS_EXPLOSION_H_
#define _GEOWARS_EXPLOSION_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Animation.h"
#include "TileSet.h"

// ---------------------------------------------------------------------------------

class Explosion : public Object
{
private:
	TileSet* tileset;
	Animation* anim;
public:
	Explosion(float pX, float pY);        // construtor
	~Explosion();                         // destrutor

	void Update();                      // atualização
	void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------

/*
inline void Explosion::Draw()
{

}
*/

// ---------------------------------------------------------------------------------


#endif