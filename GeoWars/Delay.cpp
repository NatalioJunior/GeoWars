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

// ------------------------------------------------------------------------------

Delay::Delay()
{
    logo = new Sprite("Resources/Logo.png");
    timer.Start();
    notPlayed = true;

    GeoWars::scene->Add(GeoWars::player, MOVING);
    GeoWars::scene->Add(GeoWars::gun, STATIC);
}

// ------------------------------------------------------------------------------

Delay::~Delay()
{
    delete logo;
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

    if (timer.Elapsed(6.0f))
    {
        // toca música do jogo
        GeoWars::audio->Play(THEME, true);

        //adiciona objetos na cena
        GeoWars::scene->Add(new Magenta(GeoWars::player), MOVING);
        GeoWars::scene->Add(new Blue(150.0f,150.0f, GeoWars::player), MOVING);
        GeoWars::scene->Add(new Green(GeoWars::player), MOVING);
        GeoWars::scene->Add(new Orange(150,150,180), MOVING);
        GeoWars::scene->Add(new Orange(150,150,90), MOVING);
        GeoWars::scene->Add(new Orange(2200,1500,45), MOVING);
        GeoWars::scene->Add(new Orange(2300,1500,45), MOVING);
        GeoWars::scene->Add(new Orange(2400,1500,45), MOVING);
        GeoWars::scene->Add(new Soldier(2400,1500, GeoWars::player), MOVING);
        GeoWars::scene->Add(new Soldier(2400,1500, GeoWars::player), MOVING);
        GeoWars::scene->Add(new SpawnerBase(), MOVING);
        GeoWars::scene->Add(new Orange(2400,1500,179), MOVING);
        GeoWars::scene->Delete();
    }
}

// -------------------------------------------------------------------------------

void Delay::Draw()
{
    logo->Draw(game->viewport.left + window->CenterX() , game->viewport.top + window->CenterY(), Layer::FRONT);
}

// -------------------------------------------------------------------------------
