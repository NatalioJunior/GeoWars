/**********************************************************************************
// Hud (Arquivo de Cabe�alho)
//
// Cria��o:     02 Ago 2019
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Heads Up Display
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
    enum { MENUSTART, OPTIONS, GAMEOVER, VICTORY, GAME};
    enum { SELECTED, UNSELECTED, CHECKSELECTED, UNCHECKSELECTED, CHECKUNSELECTED, UNCHECKUNSELECTED };

    Font * font = nullptr;                  // fonte para exibi��o normal
    Font * bold = nullptr;                  // fonte para exibi��o negrito

    Sprite * menuStart  = nullptr;          // pop-up do menu start
    Sprite * menuOption = nullptr;          // pop-up do menu de op��es
    Sprite * infoBox    = nullptr;          // �rea para teclas de comando do teclado
    Sprite * keyMap     = nullptr;          // �rea para teclas de comando do controle
    Sprite * ammoSprite = nullptr;          // imagem da muni��o
    Sprite * infinity   = nullptr;          // simbolo do infinito
    Sprite * slider     = nullptr;          // slider do menu

    TileSet * btnStart      = nullptr;
    TileSet * btnOptions    = nullptr;
    TileSet * btnExit       = nullptr;
    TileSet * btnApply      = nullptr;
    TileSet * btnCancel     = nullptr;
    TileSet * btnCheck      = nullptr;
    Animation * anim1       = nullptr;
    Animation * anim2       = nullptr;
    Animation * anim3       = nullptr;
    Animation * anim4       = nullptr;
    Animation * anim5       = nullptr;
    Animation * anim6       = nullptr;
    Animation * anim7       = nullptr;

    stringstream text;                      // texto tempor�rio

    uint tela;
    uint button;
    bool check1, check2, pop, apply;

    float posY, posX, applyPos;
    bool showHud = true;
    bool viewHud = true;

public:
    Hud();                                  // construtor
    ~Hud();                                 // destrutor

    void Update();                          // atualiza��o
    void Draw();                            // desenho
};

// ------------------------------------------------------------------------------

#endif

