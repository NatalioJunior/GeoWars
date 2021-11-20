#ifndef _GEOWARS_GUNS_H_
#define _GEOWARS_GUNS_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

// --------------------------------------------------------------------------------

class Guns : public Object
{
private:
    Sprite* sprite;

    Timer timer;                        // controla tempo dos disparos
    llong start;                        // marcação de início do disparo
    bool axisCtrl;                      // habilita leitura de disparos
    bool keysCtrl;                      // habilita leitura de disparos
    uint xboxPlayer;

public:
    Vector * speed;
    static int ammo;
    static bool mouseOn;

    bool AxisTimed(int axisX, int axisY, float time);
    bool KeysTimed(float time);

    Guns();                         // construtor
    ~Guns();                        // destrutor

    void Move(Vector&& v);
    void Update();                  // atualização
    void Draw();                    // desenho
};

// ------------------------------------------------------------------------------


#endif
