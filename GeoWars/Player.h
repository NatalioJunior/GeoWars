/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#ifndef _GEOWARS_PLAYER_H_
#define _GEOWARS_PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                        // objetos do jogo
#include "Sprite.h"                        // desenho de sprites
#include "Vector.h"                        // representação de vetores
#include "Particles.h"                    // sistema de partículas
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

    Guns * gun = nullptr;               // referência à arma atual do player
    Vector * speed;                     // velocidade e direção

    Player();                           // construtor
    ~Player();                          // destrutor
    
    void OnCollision(Object* obj);             // resolução da colisão
    void Move(Vector && v);             // movimenta jogador
    void Update();                      // atualização
    void Draw();                        // desenho
}; 
// ---------------------------------------------------------------------------------

#endif