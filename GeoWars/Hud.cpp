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
#include "Delay.h"

// ------------------------------------------------------------------------------

Hud::Hud()
{
    // cria fonte para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Rubik15.png");
    bold->Spacing("Resources/Rubik15.dat");

    // carrega sprites
    menuStart = new Sprite("Resources/MenuStart.jpg");
    infoBox = new Sprite("Resources/Msg12.png");
    keyMap = new Sprite("Resources/Msg13.png");
    ammoSprite = new Sprite("Resources/Ammo.png");
    infinity = new Sprite("Resources/Infinity.png");

    btnStart = new TileSet("Resources/Startbtn.png", 334, 54, 1, 2);
    anim1 = new Animation(btnStart, 0.1f, true);
    btnOptions = new TileSet("Resources/Optionsbtn.png", 334, 54, 1, 2);
    anim2 = new Animation(btnOptions, 0.1f, true);
    btnExit = new TileSet("Resources/Exitbtn.png", 334, 54, 1, 2);
    anim3 = new Animation(btnExit, 0.1f, true);

    uint selected[2] = { 0, 1};
    uint unselected[1] = { 1 };

    anim1->Add(UNSELECTED, unselected, 1);
    anim1->Add(SELECTED, selected, 2);
    anim2->Add(UNSELECTED, unselected, 1);
    anim2->Add(SELECTED, selected, 2);
    anim3->Add(UNSELECTED, unselected, 1);
    anim3->Add(SELECTED, selected, 2);

    tela = START;
    button = 0;

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
    delete menuStart;
    delete btnExit;
    delete btnOptions;
    delete btnStart;
    delete anim1;
    delete anim2;
    delete anim3;
}

// -------------------------------------------------------------------------------

void Hud::Update()
{
    switch (tela)
    {
    case GAME: 
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
        break;
    case START:
        if (window->KeyPress(VK_DOWN)) {
             button = ++button % 3;
             GeoWars::audio->Play(CURSOR);
        }
        if (window->KeyPress(VK_UP)) {
            if (button == 0) button = 3;
            button = --button % 3;
            GeoWars::audio->Play(CURSOR);
        }

        if (button == 0) {
            anim1->NextFrame();
            anim1->Select(SELECTED);
            anim2->Select(UNSELECTED);
            anim3->Select(UNSELECTED);

            if (window->KeyPress(VK_SPACE)) {
                tela = GAME;
                GeoWars::audio->Play(CONFIRM);
                GeoWars::scene->Add(new Delay(), STATIC);
            }
        }
        else if (button == 1) {
            anim2->NextFrame();
            anim1->Select(UNSELECTED);
            anim2->Select(SELECTED);
            anim3->Select(UNSELECTED);

            if (window->KeyPress(VK_SPACE)) {
                GeoWars::audio->Play(CONFIRM);
            }
        }
        else {
            anim3->NextFrame();
            anim1->Select(UNSELECTED);
            anim2->Select(UNSELECTED);
            anim3->Select(SELECTED);

            if (window->KeyPress(VK_SPACE)) {
                window->Close();
            }
        }
        break;
    default:
        break;
    }
    
}

// -------------------------------------------------------------------------------

void Hud::Draw()
{
    // define cor do texto
    Color textColor{ 0.66f, 0.65f, 0.58f, 1.0f };

    switch (tela)
    {
    case GAME:
        // desenha elementos da interface
        if (Player::ControllerOn)
            keyMap->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() - posY, Layer::FRONT);
        else
            infoBox->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() - posY, Layer::FRONT);

        ammoSprite->Draw(game->viewport.left + 50.0f, game->viewport.top + 35.0f, Layer::FRONT);

        if (Guns::ammo == -1) {
            infinity->Draw(game->viewport.left + 105.0f, game->viewport.top + 35.0f, Layer::FRONT);
        }
        else {
            // desenha texto
            text.str("");
            text << Guns::ammo;
            bold->Draw(95, 35, text.str(), textColor);
        }
        break;
    case START:
        menuStart->Draw(game->CenterX(), game->CenterY());
        anim1->Draw(game->CenterX(), game->CenterY() - 45.0f);
        anim2->Draw(game->CenterX(), game->CenterY() + 23.0f);
        anim3->Draw(game->CenterX(), game->CenterY() + 90.0f);
        break;
    default:
        break;
    }
    
}

// -------------------------------------------------------------------------------
