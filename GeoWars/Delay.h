/**********************************************************************************
// Delay (Arquivo de Cabe?alho)
//
// Cria??o:     02 Ago 2019
// Atualiza??o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri??o:   Sincroniza uma a??o
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
    bool notPlayed;         // intro n?o tocada ainda

    RandF randomX;
    RandF randomY;
    float posX, posY;

public:
    Delay();                // construtor
    ~Delay();               // destrutor

    void Update();          // atualiza??o
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
