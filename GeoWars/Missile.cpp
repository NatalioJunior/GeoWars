/**********************************************************************************
// Missile (C�digo Fonte)
// 
// Cria��o:     23 Nov 2011
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Define uma classe para um m�ssil
//
**********************************************************************************/

#include "Missile.h"
#include "WallHit.h"
#include "GeoWars.h"

// ------------------------------------------------------------------------------

Player* & Missile::player = GeoWars::player;        // refer�ncia para o player

// ------------------------------------------------------------------------------

Missile::Missile()
{
    // inicializa sprite
    sprite = new Sprite("Resources/Bullet.png");

    // cria bounding box
    BBox(new Circle(8));
    
    // inicializa velocidade
    speed.RotateTo(-player->gun->speed->Angle() - 180.0f);
    speed.ScaleTo(15.0f);
    
    // move para posi��o
    MoveTo(player->gun->X() + (30 * cos(speed.Radians())), (player->gun->Y() - 12) - (32 * sin(speed.Radians())));
    RotateTo(player->gun->speed->Angle() - 180.0f);

    // define tipo
    type = MISSILE;
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Missile::Update()
{
    // move m�ssel com vetor resultante
    Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

    // remove m�ssil da cena se ele sair da �rea de jogo
    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
    {  
        GeoWars::audio->Play(HITWALL);
        // adiciona explos�o na cena
        GeoWars::scene->Add(new WallHit(x,y), STATIC);

        // remove m�ssil da cena
        GeoWars::scene->Delete();
    }
}

// -------------------------------------------------------------------------------
