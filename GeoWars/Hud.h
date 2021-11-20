/**********************************************************************************
// Hud (Arquivo de Cabeçalho)
//
// Criação:     02 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Heads Up Display
//
**********************************************************************************/

#ifndef _GEOWARS_HUD_H_
#define _GEOWARS_HUD_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Font.h"
#include "Animation.h"
#include <sstream>
using std::stringstream;

// --------------------------------------------------------------------------------

class Hud : public Object
{
private:
    enum { START, OPTIONS, GAMEOVER, VICTORY, GAME};
    enum { SELECTED, UNSELECTED };

    Font * font = nullptr;                  // fonte para exibição normal
    Font * bold = nullptr;                  // fonte para exibição negrito

    Sprite * menuStart  = nullptr;          // pop-up do menu start
    Sprite * infoBox    = nullptr;          // área para teclas de comando do teclado
    Sprite * keyMap     = nullptr;          // área para teclas de comando do controle
    Sprite * ammoSprite = nullptr;          // imagem da munição
    Sprite * infinity   = nullptr;          // simbolo do infinito

    TileSet * btnStart      = nullptr;
    TileSet * btnOptions    = nullptr;
    TileSet * btnExit       = nullptr;
    Animation * anim1       = nullptr;
    Animation * anim2       = nullptr;
    Animation * anim3       = nullptr;

    stringstream text;                      // texto temporário

    uint tela;
    uint button;

    float posY;
    bool showHud = true;

public:
    Hud();                                  // construtor
    ~Hud();                                 // destrutor

    void Update();                          // atualização
    void Draw();                            // desenho
};

// ------------------------------------------------------------------------------

#endif

