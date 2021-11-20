/**********************************************************************************
// Magenta (Arquivo de Cabeçalho)
//
// Criação:     10 Out 2012
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz um perseguição direta
//
**********************************************************************************/

#ifndef _CHASEDEMO_MAGENTA_H_
#define _CHASEDEMO_MAGENTA_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"
#include "Timer.h"
// ---------------------------------------------------------------------------------

class Soldier : public Object
{
private:
    Sprite* sprite;                            // sprite do objeto
    Player* player;                            // ponteiro para jogador
    Vector speed;                               // velocidade e direção
    Timer timer;
public:
    Soldier(float pX, float pY, Player* p);    // construtor
    ~Soldier();                                 // destrutor

    void OnCollision(Object* obj);             // resolução da colisão
    void Update();                              // atualização
    void Draw();                                // desenho
};

// ---------------------------------------------------------------------------------

inline void Soldier::Draw()
{
    sprite->Draw(x, y, Layer::LOWER, 0.3f, rotation);
}

// ---------------------------------------------------------------------------------


#endif