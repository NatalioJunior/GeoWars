/**********************************************************************************
// WaveG (Arquivo de Cabeçalho)
//
// Criação:     06 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos Green
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
    RandF secs;             // valor aleatório de segundos
    Timer timer;            // medidor de tempo
    float delay;            // atraso para a próxima onda

public:
    SpawnerB();                // construtor
    ~SpawnerB();               // destrutor

    void Update();          // atualização
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
