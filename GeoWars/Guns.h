#ifndef _GEOWARS_GUNS_H_
#define _GEOWARS_GUNS_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 
#include "Animation.h"

// --------------------------------------------------------------------------------

enum GUNSTYPE { HANDGUN };
enum DIRECTIONGUN {NORMAL, INVERTED};

class Guns : public Object
{
private:
    static Player*& player;         // refer�ncia para o player
    TileSet* tileset;               // folha de sprites da arma
    Animation* anim;                // anima��o da arma

public:
    Vector * speed;

    Guns(uint GunType);             // construtor
    ~Guns();                        // destrutor

    void Update();                  // atualiza��o
    void Draw();                    // desenho
};

// ------------------------------------------------------------------------------


#endif
