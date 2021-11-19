
#include "Light.h"
#include "GeoWars.h"
Light::Light(float pX, float pY) {
	sprite = new Sprite("Resources/light.png");
	MoveTo(pX, pY);
	lifeTime = 0;
	timer.Start();

	time = 0.9f;
}
Light::~Light() {
	delete sprite;
}
void Light::Update() {
	time -= 3*gameTime;
	if (time <= 0)
		GeoWars::scene->Delete(this, STATIC);
}
void Light::Draw() {
	sprite->Draw(x, y, Layer::LOWER,time/2,0.0f,Color(1.0f,1.0f,0.7f,time));
}
