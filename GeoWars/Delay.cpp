/**********************************************************************************
// Delay (Código Fonte)
//
// Criação:     02 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Sincroniza uma ação
//
**********************************************************************************/

#include "Delay.h"
#include "GeoWars.h"
#include "Hud.h"
#include "SpawnerBase.h"
#include "Soldier.h"
#include "Magenta.h"
#include "Blue.h"    
#include "Green.h"
#include "Orange.h"
#include "MiniBossLarryTank.h"
#include "SpawnerA.h"
#include "SpawnerB.h"
#include "SpawnerC.h"
#include "SpawnerD.h"
#include "Oil.h"
// ------------------------------------------------------------------------------

Delay::Delay() : randomX(480.0f, 2512.0f), randomY(270.0f, 1588.0f)
{
    timer.Start();
    notPlayed = true;

    posX = randomX.Rand();
    posY = randomY.Rand();

    GeoWars::player->defeat = false;
    GeoWars::player->score = 0;
    GeoWars::player->MoveTo(game->CenterX(), game->CenterY());
    GeoWars::scene->Add(GeoWars::player, MOVING);
    GeoWars::scene->Add(GeoWars::gun, STATIC);
}

// ------------------------------------------------------------------------------

Delay::~Delay()
{
}

// -------------------------------------------------------------------------------

void Delay::Update()
{
    if (notPlayed && timer.Elapsed(2.0f))
    {
        // toca áudio de introdução
        GeoWars::audio->Play(START);
        notPlayed = false;
    }

    if (timer.Elapsed(4.0f))
    {
        // toca música do jogo
        GeoWars::audio->Play(THEME, true);

        for (int i = 0; i < 8; ++i)
        {
            GeoWars::scene->Add(new Oil(posX, posY), STATIC);

            float oldX = posX;
            float oldY = posY;

            while (abs(posX - oldX) < 200 || abs(posY - oldY) < 200)
            {
                posX = randomX.Rand();
                posY = randomY.Rand();
            }
            
        }

        //adiciona objetos na cena
        GeoWars::scene->Add(new Magenta(500,200,GeoWars::player), MOVING);
        GeoWars::scene->Add(new Blue(150.0f,150.0f, GeoWars::player), MOVING);
        GeoWars::scene->Add(new Green(500,500,GeoWars::player), MOVING);
        GeoWars::scene->Add(new Orange(150,150,180), MOVING);
        GeoWars::scene->Add(new Orange(150,150,90), MOVING);
        GeoWars::scene->Add(new Orange(2200,1500,45), MOVING);
        GeoWars::scene->Add(new Orange(2300,1500,45), MOVING);
        GeoWars::scene->Add(new Orange(2400,1500,45), MOVING);
        GeoWars::scene->Add(new Soldier(2400,1500, GeoWars::player), MOVING);
        GeoWars::scene->Add(new Soldier(2400,1500, GeoWars::player), MOVING);
        GeoWars::scene->Add(new SpawnerA(230,230,0,2), MOVING);
        GeoWars::scene->Add(new SpawnerB(2000,230,180,2), MOVING);
        GeoWars::scene->Add(new SpawnerB(230,1600,0,2), MOVING);
        GeoWars::scene->Add(new SpawnerD(2000,1500,180,2), MOVING);
        GeoWars::scene->Add(new Orange(2400,1500,179), MOVING);

        const int size1 = 11;
        Instruction larryScriptTest1[size1] =
        {
        { MOVETO, 340.0f, 0.0f, 5.0f },
        { MOVETO, 50.0f, 320.0f, 5.0f },
        { SHOOT_THREE, 0.0f, 0.0f,0.0f},
        { ROTATE, 5.0f, 8.0f, 0.8f },
        { MOVE, 90.0f, 5.0f, 0.5f },
        { MOVETO, 300.0f, 100.0f, 5.0f },
        { MOVE, 270.0f, 0.0f, 1.0f },
        { SLIDE, 180.0f, 0.5f, 5.0f },
        { SHOOT_THREE, 0.0f, 0.0f, 0.0f},
        { SLIDE, 0.0f, 0.5f, 5.0f },
        { JUMP, 6.0f, 0.0f, 0.0f }
        };
        GeoWars::scene->Add(new MiniBossLarryTank(larryScriptTest1,size1,1500,1500),MOVING);
        GeoWars::scene->Delete();
    }
}

// -------------------------------------------------------------------------------

void Delay::Draw()
{
}

// -------------------------------------------------------------------------------
