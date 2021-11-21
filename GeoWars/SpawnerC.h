
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
    float pX, pY;       // posi��o dos inimigos 
    RandF posX;         // valor aleat�rio para posi��o X
    RandF posY;         // valor aleat�rio para posi��o Y
    RandF secs;         // valor aleat�rio de segundos
    Timer timer;        // medidor de tempo
    float delay;        // atraso para a pr�xima onda

public:
    SpawnerC();            // construtor
    ~SpawnerC();           // destrutor

    void Update();      // atualiza��o
    void Draw();        // desenho
};

// ------------------------------------------------------------------------------

#endif
