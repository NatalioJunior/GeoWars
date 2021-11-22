/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#include "Player.h"
#include "GeoWars.h"
#include "Missile.h"
#include "Hud.h"
#include "Light.h"
#include "Explosion.h"


// -------------------------------------------------------------------------------

Controller* Player::gamepad = nullptr;
bool Player::ControllerOn = false;
uint Player::XboxPlayer = PLAYER1;
bool Player::defeat = false;
int Player::score = 0;
int Player::currentLife = 100;

Player::Player()
{
    // Inicializa um controler
    gamepad = new Controller();
    ControllerOn = gamepad->XboxInitialize(XboxPlayer);

    // configuração do objeto
    sprite = new Sprite("Resources/Player.png");
    speed  = new Vector(90.0f, 0.0f);

    BBox(new Rect(-37.5f, -35.0f, 37.5f, 35.0f));

    MoveTo(game->CenterX(), game->CenterY());
    type = PLAYER;

    // configuração do gerador de partículas
    Generator emitter;
    emitter.imgFile = "Resources/Tracks.png";    // arquivo de imagem
    emitter.angle = 270.0f;                     // ângulo base do emissor
    emitter.spread = 0;                        // espalhamento em graus
    emitter.lifetime = 3.0f;                    // tempo de vida em segundos
    emitter.frequency = 0.08f;                 // tempo entre geração de novas partículas
    emitter.percentToDim = 1.8f;                // desaparece após 60% da vida
    emitter.minSpeed = 0.0f;                   // velocidade mínima das partículas
    emitter.maxSpeed = 0.0f;                  // velocidade máxima das partículas
    emitter.color.r = 1.0f;                     // componente Red da partícula 
    emitter.color.g = 1.0f;                     // componente Green da partícula 
    emitter.color.b = 1.0f;                     // componente Blue da partícula 
    emitter.color.a = 1.0f;                     // transparência da partícula

    // cria sistema de partículas
    tail = new Particles(emitter);
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete sprite;
    delete speed;
    delete tail;
}


void Player::OnCollision(Object* obj) {
        if (obj->Type() == ORANGE) {
            currentLife -= 10;
            GeoWars::scene->Add(new Explosion(obj->X(), obj->Y()), STATIC);
            GeoWars::scene->Delete(obj, MOVING);
        }
        if (obj->Type() == SPAWNER) {
            motor = false;
            speed->RotateTo(speed->Angle() + 180);
            speed->ScaleTo(10.0f);
            timer.Start();
        }
        if (obj->Type() == OIL) {
            if (speed->Magnitude() > 0.1f) {
                speed->Rotate(300 * gameTime);
            }
        }

        if (obj->Type() == ENMEY_PROJECTILE) {
            currentLife -= 1;
            GeoWars::scene->Add(new Light(obj->X(), obj->Y()), STATIC);
            GeoWars::scene->Delete(obj, STATIC);
        }
}
// -------------------------------------------------------------------------------

void Player::Move(Vector && v)
{
    speed->Add(v);

    // limita velocidade máxima
    if (speed->Magnitude() > 10.0f)
        speed->ScaleTo(10.0f);

}


void Player::Reset() {
    defeat = false;
    score = 0;
    MoveTo(game->CenterX(), game->CenterY());
    currentLife = 100;
    speed->Rotate(0);
    speed->ScaleTo(0);
}
// -------------------------------------------------------------------------------

void Player::Update()
{
    // magnitude do vetor aceleração
    float accel = 40.0f * gameTime;

    if (!motor && timer.Elapsed(0.25f)) motor = true;

    if (motor) {
        if (ControllerOn) {
            gamepad->XboxUpdateState(XboxPlayer);

            float ang = Line::Angle(Point(0, 0), Point(gamepad->XboxAnalog(ThumbLX) / 327.67f, -gamepad->XboxAnalog(ThumbLY) / 327.67f));
            float mag = Point::Distance(Point(0, 0), Point(gamepad->XboxAnalog(ThumbLX) / 327.67f, -gamepad->XboxAnalog(ThumbLY) / 327.67f));

            // nenhuma direção selecionada
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
                // ande na direção selecionada
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
                // se nenhuma tecla está pressionada comece a frear
                if (speed->Magnitude() > 0.1f)
                    Move(Vector(speed->Angle() + 180.0f, 5.0f * gameTime));
                else
                    // velocidade muita baixa, não use soma vetorial, apenas pare
                    speed->ScaleTo(0.0f);
        }
    }
      
    // movimenta objeto pelo seu vetor velocidade
    Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);

    // atualiza calda do jogador
    if (speed->Magnitude() != 0.0f) 
        tail->Generate(x - 10 * cos(speed->Radians()), y + 45 * sin(speed->Radians()));
 
    tail->Config().angle = speed->Angle() + 180;
    tail->Update(gameTime);

    // restringe a área do jogo
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

    if (currentLife < 10) defeat = true;
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    sprite->Draw(x, y, Layer::UPPER, 1.0f, -speed->Angle() + 90.0f);
    tail->Draw(Layer::LOWER);
}


// -------------------------------------------------------------------------------
