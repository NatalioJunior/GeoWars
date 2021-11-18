
#ifndef SPAWNERBASE_H_
#define SPAWNERBASE_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"
#include "Sprite.h"
// --------------------------------------------------------------------------------

class SpawnerBase : public Object
{
private:
    Sprite* sprite;
    float pX, pY;           
    RandF posX;             
    RandF posY;             
    RandF secs;             
    Timer timer;            
    float delay;            

public:
    SpawnerBase();
    ~SpawnerBase();

    int life = 400;
    int currentLife = life;
    void OnCollision(Object* obj);
    void Update();          
    void Draw();            
};

// ------------------------------------------------------------------------------

#endif
