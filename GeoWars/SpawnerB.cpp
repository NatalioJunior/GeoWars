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
#include "EnemyHit.h"
#include "Explosion.h"
// ------------------------------------------------------------------------------

SpawnerB::SpawnerB(float posX, float posY, float angleSpawn, float scale) : secs(10.0f, 15.0f)
{
    // atraso para a próxima onda 
    delay = secs.Rand();
    sprite = new Sprite("Resources/SpawnerB.png");
    // posição dos inimigos

    angle = angleSpawn;
    scaleF = scale;

    BBox(new Circle(70.0f));
    MoveTo(posX, posY);
    type = SPAWNER;
}

// ------------------------------------------------------------------------------

SpawnerB::~SpawnerB()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void SpawnerB::Update()
{
    // contador de inimigos
    static uint counter = 2;

    // se passou o tempo de atraso
    if (timer.Elapsed(delay))
    {
        if (counter > 0)
        {
            // toca som de nova onda
            //BasicAI::audio->Play(GREEN);

            // adiciona nova inimigo

            Vector speed = Vector(angle, 1);
            //GeoWars::scene->Add(new Green(50, 50, GeoWars::player), MOVING);
            GeoWars::scene->Add(new Green(x + (130 * cos(speed.Radians())), y - (130 * sin(speed.Radians())), GeoWars::player), MOVING);
            //GeoWars::scene->Add(new Green(game->Width() - 50, game->Height() - 50, GeoWars::player), MOVING);
            //GeoWars::scene->Add(new Green(50, game->Height() - 50, GeoWars::player), MOVING);
            
            delay = 0.450f;
            timer.Start();
            --counter;
        }
        else
        {
            // nova onda
            counter = 2;
            delay = secs.Rand();
            timer.Start();
        }
    }
}
void SpawnerB::OnCollision(Object* obj) {
    if (obj->Type() == MISSILE) {
        GeoWars::scene->Add(new EnemyHit(obj->X(), obj->Y()), STATIC);
        GeoWars::audio->Play(HITWALL);
        GeoWars::scene->Delete(obj, STATIC);
        currentLife -= 10;
        if (currentLife <= 0) {
            GeoWars::player->score += 300;
            Vector speed = Vector(angle, 1);
            GeoWars::scene->Add(new Explosion(x - 10 + (130 * cos(speed.Radians())), y - 14 - (130 * sin(speed.Radians()))), STATIC);
            GeoWars::scene->Add(new Explosion(x + 10, y), STATIC);
            GeoWars::scene->Add(new Explosion(x - 24, y), STATIC);
            GeoWars::scene->Add(new Explosion(x + (40 * cos(speed.Radians())), 14 + y - (15 * sin(speed.Radians()))), STATIC);
            GeoWars::scene->Delete(this, MOVING);

        }
    }
}
// -------------------------------------------------------------------------------

void SpawnerB::Draw()
{
    sprite->Draw(x, y, Layer::LOWER, scaleF * scale, 0, Color(0.5f, 0.5f, 1, 1));
}

// -------------------------------------------------------------------------------
