#ifndef _GEOWARS_GUNS_H_
#define _GEOWARS_GUNS_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"

// --------------------------------------------------------------------------------

class Guns : public Object
{
private:
    Sprite* sprite;

public:
    Vector * speed;

    Guns();                         // construtor
    ~Guns();                        // destrutor

    void Update();                  // atualização
    void Draw();                    // desenho
};

// ------------------------------------------------------------------------------


#endif
