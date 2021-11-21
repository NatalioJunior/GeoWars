/**********************************************************************************
// Magenta (Arquivo de Cabeçalho)
// 
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz um perseguição direta
//
**********************************************************************************/

#ifndef _GEOWARS_MAGENTA_H_
#define _GEOWARS_MAGENTA_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"
#include "Random.h"
#include "Timer.h"

// ---------------------------------------------------------------------------------

class Magenta : public Object
{
private:
    Sprite * sprite;                    // sprite do objeto
    Vector * speed;                     // velocidade e direção
    Player * player;                    // ponteiro para jogador
    Timer timer;                    // medidor do tempo de vôo
    RandF magnitude;                // valor de magnitude aleatória
    RandF angle;                    // valor de ângulo aleatório    
    RandF secs;                     // valor de segundos aleatório
    float delay;
public:
    Magenta(float pX,float pY,Player * p);                // construtor
    ~Magenta();                         // destrutor
    
    void NewDirection();
    void OnCollision(Object * obj);     // resolução da colisão
    void Update();                      // atualização
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------

inline void Magenta::Draw()
{ sprite->Draw(x, y, Layer::LOWER, scale, rotation); }

// ---------------------------------------------------------------------------------


#endif