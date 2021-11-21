/**********************************************************************************
// WaveG (Código Fonte)
//
// Criação:     06 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos Green
//
**********************************************************************************/

#include "SpawnerB.h"
#include "GeoWars.h"
#include "Green.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

SpawnerB::SpawnerB() : secs(10.0f, 15.0f)
{
    // atraso para a próxima onda 
    delay = secs.Rand();
}

// ------------------------------------------------------------------------------

SpawnerB::~SpawnerB()
{

}

// -------------------------------------------------------------------------------

void SpawnerB::Update()
{
    // contador de inimigos
    static uint counter = 8;

    // se passou o tempo de atraso
    if (timer.Elapsed(delay))
    {
        if (counter > 0)
        {
            // toca som de nova onda
            //BasicAI::audio->Play(GREEN);

            // adiciona nova inimigo
            /*BasicAI::scene->Add(new Green(50, 50, BasicAI::player), MOVING);
            BasicAI::scene->Add(new Green(game->Width() - 50, 50, BasicAI::player), MOVING);
            BasicAI::scene->Add(new Green(game->Width() - 50, game->Height() - 50, BasicAI::player), MOVING);
            BasicAI::scene->Add(new Green(50, game->Height() - 50, BasicAI::player), MOVING);
            */
            delay = 0.450f;
            timer.Start();
            --counter;
        }
        else
        {
            // nova onda
            counter = 8;
            delay = secs.Rand();
            timer.Start();
        }
    }
}

// -------------------------------------------------------------------------------

void SpawnerB::Draw()
{

}

// -------------------------------------------------------------------------------
