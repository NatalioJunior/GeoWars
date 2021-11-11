#include "Guns.h"
#include "GeoWars.h"

Guns::Guns() {
	sprite = new Sprite("Resources/Turret.png");
	speed = new Vector(0.0f, 0.0f);
}

Guns::~Guns() {
	delete sprite;
}

void Guns::Move(Vector&& v)
{
	speed->Add(v);
}

void Guns::Update() {
	MoveTo(GeoWars::player->X(), GeoWars::player->Y());

	float delta = 240.0f * gameTime;

	if (Player::ControllerOn) {
		Player::gamepad->UpdateState();
		float ang = Line::Angle(Point(0, 0), Point(-Player::gamepad->Axis(AxisRX) / 25.0f, Player::gamepad->Axis(AxisRY) / 25.0f));
		float mag = Point::Distance(Point(0, 0), Point(Player::gamepad->Axis(AxisRX) / 25.0f, Player::gamepad->Axis(AxisRY) / 25.0f));
		if (mag != 0)
			Move(Vector(ang, 0));
	}
	else {
		if (window->KeyDown('W'))
			speed->Rotate(delta);
		if (window->KeyDown('S'))
			speed->Rotate(-delta);
	}
}

inline void Guns::Draw()
{
	sprite->Draw(GeoWars::player->X(), GeoWars::player->Y(), Layer::FRONT, scale, speed->Angle());
}

// ------------------------------------------------------------------------------