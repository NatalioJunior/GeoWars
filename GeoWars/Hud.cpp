/**********************************************************************************
// Hud (Código Fonte)
//
// Criação:     02 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Heads Up Display
//
**********************************************************************************/

#include "Hud.h"
#include "GeoWars.h"
#include "Player.h"
#include "Guns.h"

// ------------------------------------------------------------------------------

Hud::Hud()
{
    // cria fonte para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Rubik15.png");
    bold->Spacing("Resources/Rubik15.dat");

    // carrega sprites
    infoBox = new Sprite("Resources/Msg12.png");
    keyMap = new Sprite("Resources/Msg13.png");
    ammoSprite = new Sprite("Resources/Ammo.png");
    infinity = new Sprite("Resources/Infinity.png");

    posY = 64.0f;
}

// ------------------------------------------------------------------------------

Hud::~Hud()
{
    delete font;
    delete bold;
    delete infoBox;
    delete keyMap;
    delete ammoSprite;
    delete infinity;
}

// -------------------------------------------------------------------------------

void Hud::Update()
{
    if (Player::ControllerOn) {
        Player::gamepad->XboxUpdateState(Player::XboxPlayer);

        if (Player::gamepad->XboxButton(ButtonB))
            showHud = !showHud;
    }
    else {
        if (window->KeyPress('A'))
            showHud = !showHud;
    }

    if (showHud) {
        posY += 130.0f * gameTime;
        if (posY > 64.0f) posY = 64.0f;
    }
    else {
        posY -= 130.0f * gameTime;
        if (posY < -28.0f) posY = -28.0f;
    }
}

// -------------------------------------------------------------------------------

void Hud::Draw()
{
    // define cor do texto
    Color textColor{ 0.66f, 0.65f, 0.58f, 1.0f };

    // desenha elementos da interface
    if (Player::ControllerOn)
        keyMap->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() - posY, Layer::FRONT);
    else
        infoBox->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() - posY, Layer::FRONT);

    ammoSprite->Draw(game->viewport.left + 50.0f, game->viewport.top + 35.0f, Layer::FRONT);

    if (Guns::ammo == -1) {
        infinity->Draw(game->viewport.left + 105.0f, game->viewport.top + 35.0f, Layer::FRONT);
    } else {
        // desenha texto
        text.str("");
        text << Guns::ammo;
        bold->Draw(95, 35, text.str(), textColor);
    }

    //text.str("");
    //text << "Janela: " << window->Width() << " x " << window->Height();
    //font->Draw(40, 92, text.str(), textColor);
    //
    //text.str("");
    //text << "Mundo: " << game->Width() << " x " << game->Height();
    //font->Draw(40, 112, text.str(), textColor);
    //
    //text.str("");
    //text << "Viewport: (" << uint(game->viewport.left) << "," << uint(game->viewport.top) << ") a (" << uint(game->viewport.right) << "," << uint(game->viewport.bottom) << ")";
    //font->Draw(40, 132, text.str(), textColor);
    //
    //text.str("");
    //text << "Mísseis: " << GeoWars::scene->Size() - 5;
    //font->Draw(40, 152, text.str(), textColor);
}

// -------------------------------------------------------------------------------
