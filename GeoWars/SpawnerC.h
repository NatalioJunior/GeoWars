
#ifndef _PLATANK_SPAWNERC_H_
#define _PLATANK_SPAWNERC_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class SpawnerC : public Object
{
private:
    float pX, pY;       // posição dos inimigos 
    RandF posX;         // valor aleatório para posição X
    RandF posY;         // valor aleatório para posição Y
    RandF secs;         // valor aleatório de segundos
    Timer timer;        // medidor de tempo
    float delay;        // atraso para a próxima onda

public:
    SpawnerC();            // construtor
    ~SpawnerC();           // destrutor

    void Update();      // atualização
    void Draw();        // desenho
};

// ------------------------------------------------------------------------------

#endif
