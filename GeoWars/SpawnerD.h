

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
    int numX, numY;         // n�mero de inimigos que cabem na tela
    float posX, posY;       // posi��o dos inimigos 
    RandI position;         // valor aleat�rio para posi��o
    RandF delay;            // valor aleat�rio para tempo
    Timer timer;            // medidor de tempo
    float waveDelay;        // atraso para a pr�xima onda
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
    void Update();          // atualiza��o
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
