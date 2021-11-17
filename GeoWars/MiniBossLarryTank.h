
#ifndef MINIBOS_LARRYTANK_H
#define MINIBOS_LARRYTANK_H

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Vector.h"
#include "Timer.h"
#include "Player.h"
#include "Random.h"

// --------------------------------------------------------------------------------

struct Instruction
{
    int instruction;
    float angle;
    float magnitude;
    float duration;
};

// MOVE      | �ngulo    | Magnitude | Dura��o
// MOVETO    | PosX      | PosY      | Magnitude
// SLIDE     | �ngulo    | Magnitude | Dura��o
// SLIDETO   | PosX      | PosY      | Magnitude
// TURN      | �ngulo    | Magnitude | Dura��o
// ROTATE    | �ngulo    | Magnitude | Dura��o
// RANDOM    | -         | -         | Dura��o
// JUMP      | Instru��o | -         | -

enum InstructionTypes
{
    MOVE,           // move em uma dire��o e velocidade por um tempo
    MOVETO,         // move para uma posi��o x, y
    SLIDE,          // o mesmo que MOVE, por�m sem rotacionar
    SLIDETO,        // o mesmo que MOVETO, por�m sem rotacionar
    TURN,           // indica a dire��o que o objeto deve seguir
    ROTATE,         // rotaciona a dire��o do objeto por um tempo
    RANDOM,         // move em uma dire��o aleat�ria por um tempo
    JUMP            // pula para uma instru��o podendo fazer um loop
};

// ---------------------------------------------------------------------------------

class MiniBossLarryTank : public Object
{
private:
    
    //Animation* anim;                   // anima��o do objeto
    Vector * speed;                       // velocidade e dire��o
    Sprite* sprite;                    // sprite do objeto
    Instruction* script;               // vetor de instru��es
    int index;                          // �ndice da instru��o atual
    int end;                            // �ndice da �ltima instru��o
    float duration;                     // dura��o da instru��o atual

    Timer timer;                        // timer para instru��es
    RandF angle;                        // valor aleat�rio para �ngulo
    RandF magnitude;                    // valor aleat�rio para magnitude

public:
    MiniBossLarryTank(Instruction* vet, int tam, float pX, float pY);
    ~MiniBossLarryTank();

    int life = 100;

    void OnCollision(Object* obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
};




#endif