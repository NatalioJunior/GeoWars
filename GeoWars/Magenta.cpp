/**********************************************************************************
// Magenta (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz um perseguição direta
//
**********************************************************************************/

#include "GeoWars.h"
#include "Magenta.h"
#include "Random.h" 
#include "Explosion.h"
#include "Itens.h"

// ---------------------------------------------------------------------------------

Magenta::Magenta(float pX,float pY,Player * p) : magnitude(1, 4), angle(0, 359), secs(0.3f, 1.5f)
{
    player = p;
    sprite = new Sprite("Resources/Drone.png");
    speed  = new Vector(0, 2.0f);
    NewDirection();
    BBox(new Circle(18.0f));
    
    // move para uma posição aleatória (canto inferior esquerdo)
    RandF posX{ 300, 400 };
    RandF posY{ game->Height() - 400, game->Height() - 300 };
    MoveTo(pX, pY);

    type = MAGENTA;

    //Adiciona magenta ao contator
    GeoWars::nMagenta += 1;
}

// ---------------------------------------------------------------------------------

Magenta::~Magenta()
{
    delete sprite;
    delete speed;
}

// -------------------------------------------------------------------------------
void Magenta::NewDirection()
{
    // nova direção aleatória
    speed->ScaleTo(magnitude.Rand());
    speed->RotateTo(angle.Rand());

    // tempo aleatório
    delay = secs.Rand();

    // inicia medição do tempo
    timer.Start();
}
// -------------------------------------------------------------------------------

void Magenta::OnCollision(Object * obj)
{
    RandF weapon = RandF(0.0f, 1.0f);

    if (obj->Type() == MISSILE) {
        if (weapon.Rand() < 0.20f) {
            GeoWars::scene->Add(new Itens(SHOTGUN, x, y), STATIC);
        }
        GeoWars::scene->Delete(obj, STATIC);
        GeoWars::scene->Add(new Explosion(x, y), STATIC);
        GeoWars::scene->Delete(this, MOVING);
        GeoWars::nMagenta -= 1;
    }
}

// -------------------------------------------------------------------------------

void Magenta::Update()
{
    // ajusta ângulo do vetor 
    //speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    Rotate(200 * gameTime);

    // deslocamento padrão
    float delta = 100 * gameTime;

    if (timer.Elapsed(delay))
        NewDirection();

    Translate(speed->XComponent() * delta, -speed->YComponent() * delta);

    if (x < 50)
    {
        MoveTo(51, y);
        speed->RotateTo(0);
    }
    if (y < 50)
    {
        MoveTo(x, 51);
        speed->RotateTo(270);
    }
    if (x > window->Width() - 50)
    {
        MoveTo(window->Width() -51, y);
        speed->RotateTo(180);
    }
    if (y > window->Height())
    {
        MoveTo(x, window->Height()-51);
        speed->RotateTo(90);
    }


    // movimenta objeto pelo seu vetor velocidade
    //Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);
}

// -------------------------------------------------------------------------------