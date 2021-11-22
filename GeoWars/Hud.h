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
    enum { MENUSTART, OPTIONS, DEFEAT, GAME};
    enum { SELECTED, UNSELECTED, CHECKSELECTED, UNCHECKSELECTED, CHECKUNSELECTED, UNCHECKUNSELECTED };

    Font * bold = nullptr;                  // fonte para exibição negrito

    Sprite * menuStart  = nullptr;          // pop-up do menu start
    Sprite * menuOption = nullptr;          // pop-up do menu de opções
    Sprite * menuDefeat = nullptr;          // pop-up do menu de derrota
    Sprite * infoBox    = nullptr;          // área para teclas de comando do teclado
    Sprite * keyMap     = nullptr;          // área para teclas de comando do controle
    Sprite * ammoSprite = nullptr;          // imagem da munição
    Sprite * infinity   = nullptr;          // simbolo do infinito
    Sprite * slider     = nullptr;          // slider do menu
    Sprite * star       = nullptr;
    Sprite * life       = nullptr;

    TileSet * btnStart      = nullptr;
    TileSet * btnOptions    = nullptr;
    TileSet * btnExit       = nullptr;
    TileSet * btnApply      = nullptr;
    TileSet * btnCancel     = nullptr;
    TileSet * btnCheck      = nullptr;
    TileSet * btnOk         = nullptr;
    Animation * anim1       = nullptr;
    Animation * anim2       = nullptr;
    Animation * anim3       = nullptr;
    Animation * anim4       = nullptr;
    Animation * anim5       = nullptr;
    Animation * anim6       = nullptr;
    Animation * anim7       = nullptr;
    Animation * anim8       = nullptr;

    stringstream text;                      // texto temporário

    uint button;
    bool check1, check2, pop, apply;

    uint tela;
    float posY, posX, applyPos;
    bool showHud = true;
    bool viewHud = true;
    bool keyControl[12] = {true};

    bool KeysTimed(int key);

public:
    Hud();                                  // construtor
    ~Hud();                                 // destrutor

    void Update();                          // atualização
    void Draw();                            // desenho
};

// ------------------------------------------------------------------------------

#endif

