

#ifndef _PLATANK_SPAWNERD_H_
#define _PLATANK_SPAWNERD_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class SpawnerD : public Object
{
private:
    int numX, numY;         // número de inimigos que cabem na tela
    float posX, posY;       // posição dos inimigos 
    RandI position;         // valor aleatório para posição
    RandF delay;            // valor aleatório para tempo
    Timer timer;            // medidor de tempo
    float waveDelay;        // atraso para a próxima onda
    bool newWave;           // enviar nova onda
    float angle;
    float scaleF;
    float pX, pY;

    Sprite * sprite;
public:
    SpawnerD(float poX, float poY, float angleSpawn = 0, float scale = 1);                // construtor
    ~SpawnerD();               // destrutor

    int life = 200;
    int currentLife = life;
    void OnCollision(Object* obj);
    void Update();          // atualização
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
