#include "Guns.h"
#include "GeoWars.h"
#include "Missile.h"

int Guns::ammo = -1;
bool Guns::mouseOn = true;

Guns::Guns() {
	sprite = new Sprite("Resources/Turret.png");
	speed = new Vector(0.0f, 0.0f);

	xboxPlayer = Player::XboxPlayer;
	axisCtrl = true;
	keysCtrl = true;
	start = 0;
	timer.Start();
}

Guns::~Guns() {
	delete sprite;
}

void Guns::Move(Vector&& v)
{
	speed->Add(v);
}

bool Guns::AxisTimed(int axisX, int axisY, float time)
{
	// se já passou o tempo para o próximo disparo
	if (axisCtrl)
	{
		// a magnitude é a distância do eixo para o seu centro
		float magnitude = Point::Distance(Point(0, 0), Point(float(Player::gamepad->XboxAnalog(axisX)), float(Player::gamepad->XboxAnalog(axisY))));

		// se há qualquer movimento no eixo
		if (magnitude > 0.1f)
		{
			axisCtrl = false;
			start = timer.Stamp();
			return true;
		}
	}
	// senão aguarda o momento certo para testar
	else if (timer.Elapsed(start, time))
	{
		axisCtrl = true;
	}

	// eixo não acionado ou tempo não atingido
	return false;
}

bool Guns::KeysTimed(float time)
{
	// se já passou o tempo para o próximo disparo
	if (keysCtrl)
	{
		keysCtrl = false;
		start = timer.Stamp();
		return true;
	}
	// senão aguarda o momento certo
	else if (timer.Elapsed(start, time))
	{
		keysCtrl = true;
	}

	// teclas não pressionadas ou tempo não atingido
	return false;
}

void Guns::Update() {
	MoveTo(GeoWars::player->X(), GeoWars::player->Y());

	float delta = 240.0f * gameTime;

	if (Player::ControllerOn) {
		Player::gamepad->XboxUpdateState(xboxPlayer);

		//Controla a movimentação do canhão
		float ang = Line::Angle(Point(0, 0), Point(float(-Player::gamepad->XboxAnalog(ThumbRX)) / 327.67f, float(-Player::gamepad->XboxAnalog(ThumbRY)) / 327.67f));
		float mag = Point::Distance(Point(0, 0), Point(Player::gamepad->XboxAnalog(ThumbRX) / 327.67f, Player::gamepad->XboxAnalog(ThumbRY) / 327.67f));
		if (mag > 0.1f)
			Move(Vector(ang, 0));

		//Controla a frequência de disparos
		if (AxisTimed(ThumbRX, ThumbRY, 0.5f))
		{
			GeoWars::audio->Play(FIRE);
			GeoWars::scene->Add(new Missile(), STATIC);
			
		}
	}
	else {
		if (mouseOn) {
			speed->RotateTo(-Line::Angle(Point(x - game->viewport.left, y - game->viewport.top), Point(window->MouseX(), window->MouseY())) - 180.0f);

			// dispara míssil
			if (window->KeyDown(VK_LBUTTON))
			{
				if (KeysTimed(0.5f)) {
					GeoWars::audio->Play(FIRE);
					GeoWars::scene->Add(new Missile(), STATIC);
				}
			}
		}
		else {
			if (window->KeyDown('W'))
				speed->Rotate(-delta);
			if (window->KeyDown('S'))
				speed->Rotate(delta);

			// dispara míssil
			if (window->KeyDown(VK_SPACE))
			{
				if (KeysTimed(0.5f)) {
					GeoWars::audio->Play(FIRE);
					GeoWars::scene->Add(new Missile(), STATIC);
				}
			}
		}		
	}
}

inline void Guns::Draw()
{
	sprite->Draw(GeoWars::player->X(), GeoWars::player->Y(), Layer::FRONT, scale, speed->Angle());
}

// ------------------------------------------------------------------------------