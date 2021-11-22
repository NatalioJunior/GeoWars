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
    bold = new Font("Resources/Rubik15.png");
    bold->Spacing("Resources/Rubik15.dat");

    // carrega sprites
    menuStart = new Sprite("Resources/MenuStart.jpg");
    menuOption = new Sprite("Resources/MenuOptions.jpg");
    menuDefeat = new Sprite("Resources/DefeatMenu.jpg");
    infoBox = new Sprite("Resources/Msg12.png");
    keyMap = new Sprite("Resources/Msg13.png");
    ammoSprite = new Sprite("Resources/Ammo.png");
    infinity = new Sprite("Resources/Infinity.png");
    slider = new Sprite("Resources/Slider.jpg");
    star = new Sprite("Resources/Star.png");
    life = new Sprite("Resources/Life.png");

    btnStart = new TileSet("Resources/Startbtn.png", 334, 54, 1, 2);
    anim1 = new Animation(btnStart, 0.1f, true);
    btnOptions = new TileSet("Resources/Optionsbtn.png", 334, 54, 1, 2);
    anim2 = new Animation(btnOptions, 0.1f, true);
    btnExit = new TileSet("Resources/Exitbtn.png", 334, 54, 1, 2);
    anim3 = new Animation(btnExit, 0.1f, true);
    btnApply = new TileSet("Resources/Applybtn.png", 334, 54, 1, 2);
    anim4 = new Animation(btnApply, 0.1f, true);
    btnCancel = new TileSet("Resources/Cancelbtn.png", 45, 45, 1, 2);
    anim5 = new Animation(btnCancel, 0.1f, false);
    btnCheck = new TileSet("Resources/Checkbtn.png", 60, 54, 2, 4);
    anim6 = new Animation(btnCheck, 0.1f, false);
    anim7 = new Animation(btnCheck, 0.1f, false);
    btnOk = new TileSet("Resources/Okbtn.png", 334, 54, 1, 2);
    anim8 = new Animation(btnOk, 0.1f, true);

    uint selected[2] = { 0, 1};
    uint unselected[1] = { 1 };

    uint checkSelected[1] = { 3 };
    uint checkUnselected[1] = { 2 };
    uint uncheckSelected[1] = { 1 };
    uint uncheckUnselected[1] = { 0 };

    anim1->Add(UNSELECTED, unselected, 1);
    anim1->Add(SELECTED, selected, 2);
    anim2->Add(UNSELECTED, unselected, 1);
    anim2->Add(SELECTED, selected, 2);
    anim3->Add(UNSELECTED, unselected, 1);
    anim3->Add(SELECTED, selected, 2);
    anim4->Add(UNSELECTED, unselected, 1);
    anim4->Add(SELECTED, selected, 2);
    anim5->Add(UNSELECTED, unselected, 1);
    anim5->Add(SELECTED, selected, 2);
    anim8->Add(UNSELECTED, unselected, 1);
    anim8->Add(SELECTED, selected, 2);

    anim6->Add(CHECKSELECTED, checkSelected, 1);
    anim6->Add(UNCHECKSELECTED, uncheckSelected, 1);
    anim6->Add(UNCHECKUNSELECTED, uncheckUnselected, 1);
    anim6->Add(CHECKUNSELECTED, checkUnselected, 1);
    anim7->Add(CHECKSELECTED, checkSelected, 1);
    anim7->Add(UNCHECKSELECTED, uncheckSelected, 1);
    anim7->Add(UNCHECKUNSELECTED, uncheckUnselected, 1);
    anim7->Add(CHECKUNSELECTED, checkUnselected, 1);

    check1 = true;
    check2 = true;
    pop = false;
    apply = false;

    tela = MENUSTART;
    button = 0;

    posY = 64.0f;
    posX = game->viewport.left + window->CenterX();
    applyPos = posX;
}

// ------------------------------------------------------------------------------

Hud::~Hud()
{
    delete bold;
    delete infoBox;
    delete keyMap;
    delete ammoSprite;
    delete infinity;
    delete slider;
    delete star;
    delete life;
    delete menuStart;
    delete menuOption;
    delete menuDefeat;
    delete btnExit;
    delete btnOptions;
    delete btnStart;
    delete btnApply;
    delete btnCancel;
    delete btnCheck;
    delete btnOk;
    delete anim1;
    delete anim2;
    delete anim3;
    delete anim4;
    delete anim5;
    delete anim6;
    delete anim7;
    delete anim8;
}

// -------------------------------------------------------------------------------

bool Hud::KeysTimed(int key)
{
    if (Player::gamepad->XboxButton(key) && keyControl[key])
    {
        keyControl[key] = false;
        return true;
    }
    else if (!Player::gamepad->XboxButton(key))
    {
        keyControl[key] = true;
    }
    return false;
}

void Hud::Update()
{
    switch (tela)
    {
    case GAME: 
        if (Player::ControllerOn) {
            Player::gamepad->XboxUpdateState(Player::XboxPlayer);

            if (KeysTimed(ButtonB))
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
        if (Player::defeat) {
            tela = DEFEAT;
        }
        break;
    case MENUSTART:
        if (Player::ControllerOn) {
            Player::gamepad->XboxUpdateState(Player::XboxPlayer);

            if (KeysTimed(DpadUp)) {
                if (button == 0) button = 3;
                button = --button % 3;
                GeoWars::audio->Play(CURSOR);
            }
            if (KeysTimed(DpadDown)) {
                button = ++button % 3;
                GeoWars::audio->Play(CURSOR);
            }
        }
        else {
            if (window->KeyPress(VK_DOWN)) {
                button = ++button % 3;
                GeoWars::audio->Play(CURSOR);
            }
            if (window->KeyPress(VK_UP)) {
                if (button == 0) button = 3;
                button = --button % 3;
                GeoWars::audio->Play(CURSOR);
            }
        }

        if (button == 0) {
            anim1->NextFrame();
            anim1->Select(SELECTED);
            anim2->Select(UNSELECTED);
            anim3->Select(UNSELECTED);

            if (Player::ControllerOn) {
                Player::gamepad->XboxUpdateState(Player::XboxPlayer);

                if (KeysTimed(ButtonA)) {
                    GeoWars::audio->Play(CONFIRM);
                    tela = GAME;
                    GeoWars::scene->Add(new Delay(), STATIC);
                }
            }
            else {
                if (window->KeyPress(VK_SPACE)) {
                    GeoWars::audio->Play(CONFIRM);
                    tela = GAME;
                    GeoWars::scene->Add(new Delay(), STATIC);
                }
            }        
        }
        else if (button == 1) {
            anim2->NextFrame();
            anim1->Select(UNSELECTED);
            anim2->Select(SELECTED);
            anim3->Select(UNSELECTED);

            if (Player::ControllerOn) {
                Player::gamepad->XboxUpdateState(Player::XboxPlayer);

                if (KeysTimed(ButtonA)) {
                    GeoWars::audio->Play(CONFIRM);
                    tela = OPTIONS;
                }
            }
            else {
                if (window->KeyPress(VK_SPACE)) {
                    GeoWars::audio->Play(CONFIRM);
                    tela = OPTIONS;
                }
            }
        }
        else {
            anim3->NextFrame();
            anim1->Select(UNSELECTED);
            anim2->Select(UNSELECTED);
            anim3->Select(SELECTED);

            if (Player::ControllerOn) {
                Player::gamepad->XboxUpdateState(Player::XboxPlayer);

                if (KeysTimed(ButtonA)) {
                    window->Close();
                }
            }
            else {
                if (window->KeyPress(VK_SPACE)) {
                    window->Close();
                }
            }
        }
        break;
    case OPTIONS:
        if (Player::ControllerOn) {
            Player::gamepad->XboxUpdateState(Player::XboxPlayer);

            if (KeysTimed(DpadUp)) {
                if (button == 0) button = 5;
                button = --button % 5;
                GeoWars::audio->Play(CURSOR);
            }
            if (KeysTimed(DpadDown)) {
                button = ++button % 5;
                GeoWars::audio->Play(CURSOR);
            }
        }
        else {
            if (window->KeyPress(VK_DOWN)) {
                button = ++button % 5;
                GeoWars::audio->Play(CURSOR);
            }
            if (window->KeyPress(VK_UP)) {
                if (button == 0) button = 5;
                button = --button % 5;
                GeoWars::audio->Play(CURSOR);
            }
        }

        if (button == 0) {
            pop = false;
            anim5->Select(SELECTED);
            anim4->Select(UNSELECTED);
            if (check1) anim6->Select(CHECKUNSELECTED);
            else anim6->Select(UNCHECKUNSELECTED);
            if (check2) anim7->Select(CHECKUNSELECTED);
            else anim7->Select(UNCHECKUNSELECTED);

            if (Player::ControllerOn) {
                Player::gamepad->XboxUpdateState(Player::XboxPlayer);

                if (KeysTimed(ButtonA)) {
                    GeoWars::audio->Play(CANCEL);
                    if (!apply) posX = applyPos;
                    apply = false;
                    tela = MENUSTART;
                }
            }
            else {
                if (window->KeyPress(VK_SPACE)) {
                    GeoWars::audio->Play(CANCEL);
                    if (!apply) posX = applyPos;
                    apply = false;
                    tela = MENUSTART;
                }
            }
        }
        else if (button == 1) {
            pop = false;
            if (check1) anim6->Select(CHECKSELECTED);
            else anim6->Select(UNCHECKSELECTED);

            if (check2) anim7->Select(CHECKUNSELECTED);
            else anim7->Select(UNCHECKUNSELECTED);

            anim4->Select(UNSELECTED);
            anim5->Select(UNSELECTED);

            if (Player::ControllerOn) {
                Player::gamepad->XboxUpdateState(Player::XboxPlayer);

                if (KeysTimed(ButtonA)) {
                    check1 = !check1;
                    Guns::mouseOn = !Guns::mouseOn;
                    window->HideCursor(!check1);
                }
            }
            else {
                if (window->KeyPress(VK_SPACE)) {
                    check1 = !check1;
                    Guns::mouseOn = !Guns::mouseOn;
                    window->HideCursor(!check1);
                }
            }
        }
        else if (button == 2) {
            pop = false;
            if (check2) anim7->Select(CHECKSELECTED);
            else anim7->Select(UNCHECKSELECTED);
            if (check1) anim6->Select(CHECKUNSELECTED);
            else anim6->Select(UNCHECKUNSELECTED);
            anim4->Select(UNSELECTED);
            anim5->Select(UNSELECTED);

            if (Player::ControllerOn) {
                Player::gamepad->XboxUpdateState(Player::XboxPlayer);

                if (KeysTimed(ButtonA)) {
                    check2 = !check2;
                    viewHud = !viewHud;
                }
            }
            else {
                if (window->KeyPress(VK_SPACE)) {
                    check2 = !check2;
                    viewHud = !viewHud;
                }
            }
        }
        else if (button == 3) {
            pop = true;

            anim4->Select(UNSELECTED);
            anim5->Select(UNSELECTED);
            if (check1) anim6->Select(CHECKUNSELECTED);
            else anim6->Select(UNCHECKUNSELECTED);
            if (check2) anim7->Select(CHECKUNSELECTED);
            else anim7->Select(UNCHECKUNSELECTED);

            if (Player::ControllerOn) {
                Player::gamepad->XboxUpdateState(Player::XboxPlayer);

                if (KeysTimed(DpadLeft)) {
                    GeoWars::audio->Play(POP);
                    posX -= 53.2f;
                    if (posX < 1813.0f) posX = 1813.0f;
                }

                if (KeysTimed(DpadRight)) {
                    GeoWars::audio->Play(POP);
                    posX += 53.2f;
                    if (posX > 2026.0f) posX = 2026.0f;
                }
            }
            else {
                if (window->KeyPress(VK_RIGHT)) {
                    GeoWars::audio->Play(POP);
                    posX += 53.2f;
                    if (posX > 2026.0f) posX = 2026.0f;
                }
                if (window->KeyPress(VK_LEFT)) {
                    GeoWars::audio->Play(POP);
                    posX -= 53.2f;
                    if (posX < 1813.0f) posX = 1813.0f;
                }
            }
        }
        else {
            pop = false;
            anim4->NextFrame();
            anim4->Select(SELECTED);
            anim5->Select(UNSELECTED);
            if (check1) anim6->Select(CHECKUNSELECTED);
            else anim6->Select(UNCHECKUNSELECTED);
            if (check2) anim7->Select(CHECKUNSELECTED);
            else anim7->Select(UNCHECKUNSELECTED);

            if (Player::ControllerOn) {
                Player::gamepad->XboxUpdateState(Player::XboxPlayer);

                if (KeysTimed(ButtonA)) {
                    GeoWars::audio->Play(APPLY);
                    applyPos = posX;
                    GeoWars::audio->Volume(THEME, (posX - 1813.0f) / 216.0f);
                    GeoWars::audio->Volume(FIRE, (posX - 1813.0f) / 216.0f);
                    GeoWars::audio->Volume(HITWALL, ((posX - 1813.0f) / 216.0f) - 0.45f);
                    GeoWars::audio->Volume(EXPLODE, (posX - 1813.0f) / 216.0f);
                    GeoWars::audio->Volume(START, (posX - 1813.0f) / 216.0f);
                }
            }
            else {
                if (window->KeyPress(VK_SPACE)) {
                    GeoWars::audio->Play(APPLY);
                    applyPos = posX;
                    GeoWars::audio->Volume(THEME, (posX - 1813.0f) / 216.0f);
                    GeoWars::audio->Volume(FIRE, (posX - 1813.0f) / 216.0f);
                    GeoWars::audio->Volume(HITWALL, (posX - 1813.0f) / 216.0f);
                    GeoWars::audio->Volume(EXPLODE, (posX - 1813.0f) / 216.0f);
                    GeoWars::audio->Volume(START, (posX - 1813.0f) / 216.0f);
                }
            }
        }
        break;
    case DEFEAT:
        anim8->Select(SELECTED);
        anim8->NextFrame();

        if (Player::ControllerOn) {
            Player::gamepad->XboxUpdateState(Player::XboxPlayer);

            if (KeysTimed(ButtonA)) {
                GeoWars::audio->Play(CONFIRM);
                tela = MENUSTART;
            }
        }
        else {
            if (window->KeyPress(VK_SPACE)) {
                GeoWars::audio->Play(CONFIRM);
                tela = MENUSTART;
            }
        }
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
        if (viewHud) {
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

            int l = Player::currentLife / 10;
            for (int i = 0; i < l; i++) {
                life->Draw(game->viewport.left + 1105.0f - 20.0f * i, game->viewport.top + 35.0f, Layer::FRONT);
            }
        }       
        break;
    case MENUSTART:
        menuStart->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2);
        anim1->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2 - 45.0f);
        anim2->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2 + 23.0f);
        anim3->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2 + 90.0f);
        break;
    case OPTIONS:
        menuOption->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2);
        anim4->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2 + 214.0f);
        anim5->Draw(game->viewport.left + window->CenterX() + 185.0f, game->viewport.top + window->Height() / 2 - 145.0f);
        anim6->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2 - 80.0f);
        anim7->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2 + 35.0f);
        if (pop) slider->Draw(posX, game->viewport.top + window->Height() / 2 + 155.0f);
        else slider->Draw(posX, game->viewport.top + window->Height() / 2 + 155.0f, Layer::MIDDLE, 1.0f, 0, Color{ 0.416f, 1.0f, 0.322f, 1.0f });
        break;

    case DEFEAT:
        int score = Player::score;
        text.str("");
        text << score;
        bold->Draw(window->CenterX(), window->CenterY() + 50.0f, text.str(), textColor);
        menuDefeat->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2);
        anim8->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2 + 130.0f);
        if (score >= 500) {
            star->Draw(game->viewport.left + window->CenterX() - 220.0f, game->viewport.top + window->Height() / 2 - 50.0f);
        }
        if (score >= 1000) {
            star->Draw(game->viewport.left + window->CenterX() + 220.0f, game->viewport.top + window->Height() / 2 - 50.0f);
        }
        if (score >= 2000) {
            star->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() / 2 - 50.0f, Layer::MIDDLE, 1.15f);
        }
        break;
    }
    
}

// -------------------------------------------------------------------------------
