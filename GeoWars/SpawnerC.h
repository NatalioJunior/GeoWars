
#ifndef _PLATANK_SPAWNERC_H_
#define _PLATANK_SPAWNERC_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"
#include "Sprite.h"

// --------------------------------------------------------------------------------

class SpawnerC : public Object
{
private:
    float pX, pY;       // posi��o dos inimigos 

    RandF secs;         // valor aleat�rio de segundos
    Timer timer;        // medidor de tempo
    float delay;        // atraso para a pr�xima onda
    float angle;
    float scaleF;
    Sprite* sprite;
public:
    SpawnerC(float posX, float posY, float angleSpawn = 0, float scale = 1);            // construtor
    ~SpawnerC();           // destrutor

    int life = 200;
    int currentLife = life;
    void OnCollision(Object* obj);
    void Update();      // atualiza��o
    void Draw();        // desenho
};

// ------------------------------------------------------------------------------

#endif
