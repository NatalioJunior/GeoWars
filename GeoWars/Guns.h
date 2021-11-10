#ifndef _GEOWARS_GUNS_H_
#define _GEOWARS_GUNS_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Animation.h"

// --------------------------------------------------------------------------------

enum GUNSTYPE { HANDGUN };
enum DIRECTIONGUN {NORMAL, INVERTED};

class Guns : public Object
{
private:
    TileSet* tileset = nullptr;               // folha de sprites da arma
    Animation* anim = nullptr;                // animação da arma

public:
    Vector * speed;

    Guns(uint GunType);             // construtor
    ~Guns();                        // destrutor

    void Update();                  // atualização
    void Draw();                    // desenho
};

// ------------------------------------------------------------------------------


#endif
