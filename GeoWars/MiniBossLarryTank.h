
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

// MOVE      | Ângulo    | Magnitude | Duração
// MOVETO    | PosX      | PosY      | Magnitude
// SLIDE     | Ângulo    | Magnitude | Duração
// SLIDETO   | PosX      | PosY      | Magnitude
// TURN      | Ângulo    | Magnitude | Duração
// ROTATE    | Ângulo    | Magnitude | Duração
// RANDOM    | -         | -         | Duração
// JUMP      | Instrução | -         | -

enum InstructionTypes
{
    MOVE,           // move em uma direção e velocidade por um tempo
    MOVETO,         // move para uma posição x, y
    SLIDE,          // o mesmo que MOVE, porém sem rotacionar
    SLIDETO,        // o mesmo que MOVETO, porém sem rotacionar
    TURN,           // indica a direção que o objeto deve seguir
    ROTATE,         // rotaciona a direção do objeto por um tempo
    RANDOM,         // move em uma direção aleatória por um tempo
    JUMP            // pula para uma instrução podendo fazer um loop
};

// ---------------------------------------------------------------------------------

class MiniBossLarryTank : public Object
{
private:
    
    //Animation* anim;                   // animação do objeto
    Vector * speed;                       // velocidade e direção
    Sprite* sprite;                    // sprite do objeto
    Instruction* script;               // vetor de instruções
    int index;                          // índice da instrução atual
    int end;                            // índice da última instrução
    float duration;                     // duração da instrução atual

    Timer timer;                        // timer para instruções
    RandF angle;                        // valor aleatório para ângulo
    RandF magnitude;                    // valor aleatório para magnitude

public:
    MiniBossLarryTank(Instruction* vet, int tam, float pX, float pY);
    ~MiniBossLarryTank();

    int life = 100;

    void OnCollision(Object* obj);     // resolução da colisão
    void Update();                      // atualização
    void Draw();                        // desenho
};




#endif