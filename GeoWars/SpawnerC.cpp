
#include "SpawnerC.h"
#include "GeoWars.h"
#include "Magenta.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

SpawnerC::SpawnerC(float poX, float poY, float angleSpawn, float scale) :secs(2.0f, 4.0f)
{
    sprite = new Sprite("Resources/Player.png");
    // posição dos inimigos
    pX = poX;
    pY = poY;
    angle = angleSpawn;
    scaleF = scale;

    // atraso para a próxima onda 
    delay = secs.Rand();
    Point vertex[4] =
    {
        Point(-75.0f,-70.0f), Point(75.0f,-70.0f), Point(75.0f,70.0f), Point(-75.0f, 70.0f)
    };
    BBox(new Poly(vertex, 4));
    MoveTo(pX, pY);
    type = SPAWNER;
}

// ------------------------------------------------------------------------------

SpawnerC::~SpawnerC()
{
    delete sprite;
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

        Vector speed = Vector(angle, 1);
        GeoWars::scene->Add(new Magenta(x + (45 * cos(speed.Radians())), y - (45 * sin(speed.Radians())), GeoWars::player), MOVING);


        // reinicia o timer
        timer.Start();
    }
}

// -------------------------------------------------------------------------------

void SpawnerC::Draw()
{
    sprite->Draw(x, y, Layer::UPPER, scaleF * scale, 0, Color(1, 1, 1, 1));
}

// -------------------------------------------------------------------------------
