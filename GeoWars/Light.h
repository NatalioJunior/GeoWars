
#ifndef LIGHT_H_
#define LIGHT_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Timer.h"

// ---------------------------------------------------------------------------------

class Light : public Object
{
private:
    Sprite* sprite;                    // sprite do objeto
    llong lifeTime;
    float time;
    Timer timer;
    //float factor;                       // fator de escala


public:
    Light(float pX, float pY);                   // construtor
    ~Light();                            // destrutor

    
    void Update();                      // atualização
    void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------



// ---------------------------------------------------------------------------------


#endif