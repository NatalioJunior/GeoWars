/**********************************************************************************
// WaveG (Arquivo de Cabe�alho)
//
// Cria��o:     06 Ago 2019
// Atualiza��o: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Cria uma onda de inimigos Green
//
**********************************************************************************/

#ifndef _PLATANK_SPAWNERB_H_
#define _PLATANK_SPAWNERB_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class SpawnerB : public Object
{
private:
    RandF secs;             // valor aleat�rio de segundos
    Timer timer;            // medidor de tempo
    float delay;            // atraso para a pr�xima onda

public:
    SpawnerB();                // construtor
    ~SpawnerB();               // destrutor

    void Update();          // atualiza��o
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
