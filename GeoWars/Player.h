/**********************************************************************************
// Player (Arquivo de Cabe�alho)
// 
// Cria��o:     10 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Define a classe jogador
//
**********************************************************************************/

#ifndef _GEOWARS_PLAYER_H_
#define _GEOWARS_PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                        // objetos do jogo
#include "Sprite.h"                        // desenho de sprites
#include "Vector.h"                        // representa��o de vetores
#include "Particles.h"                    // sistema de part�culas
#include "Guns.h"
#include "Controller.h"

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    Sprite * sprite;                    // sprite do objeto
    Particles * tail;                   // calda do jogador


public:
    static Controller* gamepad;                // controle de jogo
    static bool ControllerOn;
    static uint XboxPlayer;
    static bool defeat;
    static int score;

    Guns * gun = nullptr;               // refer�ncia � arma atual do player
    Vector * speed;                     // velocidade e dire��o

    Player();                           // construtor
    ~Player();                          // destrutor
    
    void OnCollision(Object* obj);             // resolu��o da colis�o
    void Move(Vector && v);             // movimenta jogador
    void Update();                      // atualiza��o
    void Draw();                        // desenho
}; 
// ---------------------------------------------------------------------------------

#endif