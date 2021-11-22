#ifndef _GEOWARS_ITENS_H_
#define _GEOWARS_ITENS_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

// --------------------------------------------------------------------------------

class Itens : public Object
{
private:
    Sprite* sprite = nullptr;
    float factor;
    Timer timer;

public:
    Itens(uint item, float posX, float posY);     // construtor
    ~Itens();                                     // destrutor

    void Update();                  // atualização
    void Draw();                    // desenho
};

// ------------------------------------------------------------------------------


#endif
