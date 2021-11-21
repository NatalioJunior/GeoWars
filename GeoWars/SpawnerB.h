
#ifndef _PLATANK_SPAWNERB_H_
#define _PLATANK_SPAWNERB_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"
#include "Sprite.h"
// --------------------------------------------------------------------------------

class SpawnerB : public Object
{
private:
    RandF secs;             // valor aleatório de segundos
    Timer timer;            // medidor de tempo
    float delay;            // atraso para a próxima onda
    float angle;
    float scaleF;
    Sprite* sprite;
public:
    SpawnerB(float posX, float posY, float angleSpawn = 0, float scale = 1);                // construtor
    ~SpawnerB();               // destrutor

    int life = 200;
    int currentLife = life;
    void OnCollision(Object* obj);
    void Update();          // atualização
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
