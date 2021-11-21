
#include "SpawnerC.h"
#include "GeoWars.h"
#include "Magenta.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

SpawnerC::SpawnerC() : posX(50, window->Width() - 50), posY(50, game->Height() - 50), secs(2.0f, 4.0f)
{
    // posição dos inimigos
    pX = posX.Rand();
    pY = posY.Rand();

    // atraso para a próxima onda 
    delay = secs.Rand();
}

// ------------------------------------------------------------------------------

SpawnerC::~SpawnerC()
{

}

// -------------------------------------------------------------------------------

void SpawnerC::Update()
{
    // se passou o tempo de atraso
    if (timer.Elapsed(delay) )
    {
        // toca som de nova onda
        //BasicAI::audio->Play(MAGENTA);

        // adiciona novo inimigo
      //  BasicAI::scene->Add(new Magenta(pX, pY, BasicAI::player), MOVING);

        // nova posição do inimigo
        pX = posX.Rand();
        pY = posY.Rand();

        // reinicia o timer
        timer.Start();
    }
}

// -------------------------------------------------------------------------------

void SpawnerC::Draw()
{

}

// -------------------------------------------------------------------------------
