#ifndef _GEOWARS_OIL_H_
#define _GEOWARS_OIL_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                        // objetos do jogo
#include "Sprite.h"                        // desenho de sprites

// ---------------------------------------------------------------------------------

class Oil : public Object
{
private:
    Sprite* sprite;                    // sprite do objeto

public:

    Oil(float pX, float pY);                           // construtor
    ~Oil();                          // destrutor

    void Update();                      // atualização
    void Draw();                        // desenho
};
// ---------------------------------------------------------------------------------

#endif

