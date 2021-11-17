/**********************************************************************************
// Player (C�digo Fonte)
// 
// Cria��o:     10 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Define a classe jogador
//
**********************************************************************************/

#include "Player.h"
#include "GeoWars.h"
#include "Missile.h"

// -------------------------------------------------------------------------------

Controller* Player::gamepad = nullptr;
bool Player::ControllerOn = false;
uint Player::XboxPlayer = PLAYER1;

Player::Player()
{
    // Inicializa um controler
    gamepad = new Controller();
    ControllerOn = gamepad->XboxInitialize(XboxPlayer);

    // configura��o do objeto
    sprite = new Sprite("Resources/Player.png");
    speed  = new Vector(90.0f, 0.0f);

    Point vertex[4] =
    {
        Point(-37.5f,-35.0f), Point(37.5f,-35.0f), Point(37.5f,35.0f), Point(-37.0f, 35.0f)
    };
    BBox(new Poly(vertex, 4));

    MoveTo(game->CenterX(), game->CenterY());
    type = PLAYER;

    // configura��o do gerador de part�culas
    Generator emitter;
    emitter.imgFile = "Resources/Tracks.png";    // arquivo de imagem
    emitter.angle = 270.0f;                     // �ngulo base do emissor
    emitter.spread = 0;                        // espalhamento em graus
    emitter.lifetime = 3.0f;                    // tempo de vida em segundos
    emitter.frequency = 0.08f;                 // tempo entre gera��o de novas part�culas
    emitter.percentToDim = 1.8f;                // desaparece ap�s 60% da vida
    emitter.minSpeed = 0.0f;                   // velocidade m�nima das part�culas
    emitter.maxSpeed = 0.0f;                  // velocidade m�xima das part�culas
    emitter.color.r = 1.0f;                     // componente Red da part�cula 
    emitter.color.g = 1.0f;                     // componente Green da part�cula 
    emitter.color.b = 1.0f;                     // componente Blue da part�cula 
    emitter.color.a = 1.0f;                     // transpar�ncia da part�cula

    // cria sistema de part�culas
    tail = new Particles(emitter);
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete sprite;
    delete speed;
    delete tail;
}

// -------------------------------------------------------------------------------

void Player::Move(Vector && v)
{
    speed->Add(v);

    // limita velocidade m�xima
    if (speed->Magnitude() > 10.0f)
        speed->ScaleTo(10.0f);

}

// -------------------------------------------------------------------------------

void Player::Update()
{
    // magnitude do vetor acelera��o
    float accel = 40.0f * gameTime;

    if (ControllerOn) {
        gamepad->XboxUpdateState(XboxPlayer);

        float ang = Line::Angle(Point(0, 0), Point(gamepad->XboxAnalog(ThumbLX) / 327.67f, -gamepad->XboxAnalog(ThumbLY) / 327.67f));
        float mag = Point::Distance(Point(0, 0), Point(gamepad->XboxAnalog(ThumbLX) / 327.67f, -gamepad->XboxAnalog(ThumbLY) / 327.67f));

        // nenhuma dire��o selecionada
        if (mag == 0)
        {
            // se a velocidade estiver muita baixa
            if (speed->Magnitude() < 0.1)
            {
                // apenas pare
                speed->ScaleTo(0.0f);
            }
            else
            {
                // comece a frear
                Move(Vector(speed->Angle() + 180.0f, 5.0f * gameTime));
            }
        }
        else
        {
            // ande na dire��o selecionada
            Move(Vector(ang, mag * gameTime));
        }

    }
    else {
        // modifica vetor velocidade do player
        if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_UP))
            Move(Vector(45.0f, accel));
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_UP))
            Move(Vector(135.0f, accel));
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_DOWN))
            Move(Vector(225.0f, accel));
        else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_DOWN))
            Move(Vector(315.0f, accel));
        else if (window->KeyDown(VK_RIGHT))
            Move(Vector(0.0f, accel));
        else if (window->KeyDown(VK_LEFT))
            Move(Vector(180.0f, accel));
        else if (window->KeyDown(VK_UP))
            Move(Vector(90.0f, accel));
        else if (window->KeyDown(VK_DOWN))
            Move(Vector(270.0f, accel));
        else
            // se nenhuma tecla est� pressionada comece a frear
            if (speed->Magnitude() > 0.1f)
                Move(Vector(speed->Angle() + 180.0f, 5.0f * gameTime));
            else
                // velocidade muita baixa, n�o use soma vetorial, apenas pare
                speed->ScaleTo(0.0f);
    }
    
    // movimenta objeto pelo seu vetor velocidade
    Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);

    // atualiza calda do jogador
    if (speed->Magnitude() != 0.0f) 
        tail->Generate(x - 10 * cos(speed->Radians()), y + 45 * sin(speed->Radians()));
 
    tail->Config().angle = speed->Angle() + 180;
    tail->Update(gameTime);

    // restringe a �rea do jogo
    if (x < 85)
        MoveTo(85, y);
    if (y < 85)
        MoveTo(x, 85);
    if (x > game->Width() - 85)
        MoveTo(game->Width() - 85, y);
    if (y > game->Height() - 85)
        MoveTo(x, game->Height() - 85);

    //Rotaciona o object para que seu bbox use o angulo calculado
    RotateTo(-speed->Angle() + 90.0f);
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    sprite->Draw(x, y, Layer::UPPER, 1.0f, -speed->Angle() + 90.0f);
    tail->Draw(Layer::LOWER);
}


// -------------------------------------------------------------------------------
