#include "Guns.h"
#include "GeoWars.h"
#include "Missile.h"
#include "Projectile.h"
#include "PlasmaBall.h"
#include "Light.h"
#include "MachinegunProjectile.h"
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

	activeGun = 0;
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
	// se j� passou o tempo para o pr�ximo disparo
	if (axisCtrl)
	{
		// a magnitude � a dist�ncia do eixo para o seu centro
		float magnitude = Point::Distance(Point(0, 0), Point(float(Player::gamepad->XboxAnalog(axisX)), float(Player::gamepad->XboxAnalog(axisY))));

		// se h� qualquer movimento no eixo
		if (magnitude > 0.1f)
		{
			axisCtrl = false;
			start = timer.Stamp();
			return true;
		}
	}
	// sen�o aguarda o momento certo para testar
	else if (timer.Elapsed(start, time))
	{
		axisCtrl = true;
	}

	// eixo n�o acionado ou tempo n�o atingido
	return false;
}

bool Guns::KeysTimed(float time)
{
	// se j� passou o tempo para o pr�ximo disparo
	if (keysCtrl)
	{
		keysCtrl = false;
		start = timer.Stamp();
		return true;
	}
	// sen�o aguarda o momento certo
	else if (timer.Elapsed(start, time))
	{
		keysCtrl = true;
	}

	// teclas n�o pressionadas ou tempo n�o atingido
	return false;
}

void Guns::Update() {
	MoveTo(GeoWars::player->X(), GeoWars::player->Y());

	float delta = 240.0f * gameTime;

	if (Player::ControllerOn) {
		Player::gamepad->XboxUpdateState(xboxPlayer);

		//Controla a movimenta��o do canh�o
		float ang = Line::Angle(Point(0, 0), Point(float(-Player::gamepad->XboxAnalog(ThumbRX)) / 327.67f, float(-Player::gamepad->XboxAnalog(ThumbRY)) / 327.67f));
		float mag = Point::Distance(Point(0, 0), Point(Player::gamepad->XboxAnalog(ThumbRX) / 327.67f, Player::gamepad->XboxAnalog(ThumbRY) / 327.67f));
		if (mag > 0.1f)
			Move(Vector(ang, 0));

		switch (activeGun)
		{
		case 0:
			if (AxisTimed(ThumbRX, ThumbRY, 0.5f))
			{
				GeoWars::scene->Add(new Light(x, y), STATIC);
				GeoWars::audio->Play(FIRE);
				GeoWars::scene->Add(new Missile(), STATIC);

			}
			break;
		case 1:
			if (AxisTimed(ThumbRX, ThumbRY, 0.9f))
			{
				GeoWars::audio->Play(FIRE);
				GeoWars::scene->Add(new Light(x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians()))), STATIC);
				GeoWars::scene->Add(
					new PlasmaBall(
						x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians())),
						-speed->Angle() - 170, 2.0f),
					STATIC);
				GeoWars::scene->Add(
					new PlasmaBall(
						x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians())),
						-speed->Angle() - 180, 2.0f),
					STATIC);
				GeoWars::scene->Add(
					new PlasmaBall(
						x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians())),
						-speed->Angle() - 190, 2.0f),
					STATIC);
				ammo -= 3;

			}
			break;
		case 2:
			if (AxisTimed(ThumbRX, ThumbRY, 0.13f))
			{
				GeoWars::scene->Add(new Light(x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians()))), STATIC);
				GeoWars::audio->Play(FIRE);
				GeoWars::scene->Add(new MachineGunProjectile(x + 10 - (45 * cos(speed->Radians())), y + (cos(-speed->Angle() - 180) * 10) - (45 * sin(speed->Radians())),
					-speed->Angle() - 180, 0.3f),
					STATIC);
				GeoWars::scene->Add(new MachineGunProjectile(x - 10 - (45 * cos(speed->Radians())), y - (cos(-speed->Angle() - 180) * 10) - (45 * sin(speed->Radians())),
					-speed->Angle() - 180, 0.3f),
					STATIC);
				ammo -= 2;

			}
			break;
		}

		//Controla a frequ�ncia de disparos
		if (AxisTimed(ThumbRX, ThumbRY, 0.5f))
		{
			GeoWars::audio->Play(FIRE);
			GeoWars::scene->Add(new Missile(), STATIC);

		}
	}
	else {

		if (mouseOn) {
			speed->RotateTo(-Line::Angle(Point(x - game->viewport.left, y - game->viewport.top), Point(window->MouseX(), window->MouseY())) - 180.0f);

			// dispara m�ssil
			if (window->KeyDown(VK_LBUTTON))
			{
				switch (activeGun)
				{
				case 0:
					if (KeysTimed(0.5f)) {
						GeoWars::scene->Add(new Light(x, y), STATIC);
						GeoWars::audio->Play(FIRE);
						GeoWars::scene->Add(new Missile(), STATIC);
					}
					break;
				case 1:
					if (KeysTimed(0.9f)) {
						GeoWars::audio->Play(FIRE);
						GeoWars::scene->Add(new Light(x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians()))), STATIC);
						GeoWars::scene->Add(
							new PlasmaBall(
								x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians())),
								-speed->Angle() - 170, 2.0f),
							STATIC);
						GeoWars::scene->Add(
							new PlasmaBall(
								x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians())),
								-speed->Angle() - 180, 2.0f),
							STATIC);
						GeoWars::scene->Add(
							new PlasmaBall(
								x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians())),
								-speed->Angle() - 190, 2.0f),
							STATIC);
						ammo -= 3;

					}
					break;
				case 2:
					if (KeysTimed(0.13f)) {
						GeoWars::scene->Add(new Light(x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians()))), STATIC);
						GeoWars::audio->Play(FIRE);
						GeoWars::scene->Add(new MachineGunProjectile(x + 10 - (45 * cos(speed->Radians())), y + (cos(-speed->Angle() - 180) * 10) - (45 * sin(speed->Radians())),
							-speed->Angle() - 180, 0.3f),
							STATIC);
						GeoWars::scene->Add(new MachineGunProjectile(x - 10 - (45 * cos(speed->Radians())), y - (cos(-speed->Angle() - 180) * 10) - (45 * sin(speed->Radians())),
							-speed->Angle() - 180, 0.3f),
							STATIC);
						ammo -= 2;
					}
					break;
				}
			}

		}
		else {
			if (window->KeyDown('W'))
				speed->Rotate(-delta);
			if (window->KeyDown('S'))
				speed->Rotate(delta);

			// dispara m�ssil
			if (window->KeyDown(VK_SPACE))
			{
				switch (activeGun)
				{
				case 0:
					if (KeysTimed(0.5f)) {
						GeoWars::scene->Add(new Light(x, y), STATIC);
						GeoWars::audio->Play(FIRE);
						GeoWars::scene->Add(new Missile(), STATIC);
					}
					break;
				case 1:
					if (KeysTimed(0.9f)) {
						GeoWars::audio->Play(FIRE);
						GeoWars::scene->Add(new Light(x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians()))), STATIC);
						GeoWars::scene->Add(
							new PlasmaBall(
								x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians())),
								-speed->Angle() - 170, 2.0f),
							STATIC);
						GeoWars::scene->Add(
							new PlasmaBall(
								x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians())),
								-speed->Angle() - 180, 2.0f),
							STATIC);
						GeoWars::scene->Add(
							new PlasmaBall(
								x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians())),
								-speed->Angle() - 190, 2.0f),
							STATIC);
						ammo -= 3;

					}
					break;
				case 2:
					if (KeysTimed(0.13f)) {
						GeoWars::scene->Add(new Light(x - (45 * cos(speed->Radians())), y - (45 * sin(speed->Radians()))), STATIC);
						GeoWars::audio->Play(FIRE);
						GeoWars::scene->Add(new MachineGunProjectile(x + 10 - (45 * cos(speed->Radians())), y + (cos(-speed->Angle() - 180) * 10) - (45 * sin(speed->Radians())),
							-speed->Angle() - 180, 0.3f),
							STATIC);
						GeoWars::scene->Add(new MachineGunProjectile(x - 10 - (45 * cos(speed->Radians())), y - (cos(-speed->Angle() - 180) * 10) - (45 * sin(speed->Radians())),
							-speed->Angle() - 180, 0.3f),
							STATIC);
						ammo -= 2;
					}
					break;
				}
			}
		}
		if (ammo <= 0) {
			activeGun = 0;
			ammo = -1;
		}
	}

}

inline void Guns::Draw()
{
	sprite->Draw(GeoWars::player->X(), GeoWars::player->Y(), Layer::FRONT, scale, speed->Angle());
}

// ------------------------------------------------------------------------------