/**********************************************************************************
// Delay (Arquivo de Cabeçalho)
//
// Criação:     02 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Sincroniza uma ação
//
**********************************************************************************/

#ifndef _GEOWARS_DELAY_H_
#define _GEOWARS_DELAY_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class Delay : public Object
{
private:
    Timer timer;            // medidor de tempo
    bool notPlayed;         // intro não tocada ainda

    RandF randomX;
    RandF randomY;
    float posX, posY;

public:
    Delay();                // construtor
    ~Delay();               // destrutor

    void Update();          // atualização
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
