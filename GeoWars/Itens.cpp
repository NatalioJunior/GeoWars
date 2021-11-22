#include "Itens.h"
#include "GeoWars.h"

Itens::Itens(uint item, float posX, float posY) {
	switch (item)
	{
	case HEAVY: sprite = new Sprite("Resources/HeavyMachineGun.png"); type = HEAVYITEM; break;
	case SHOTGUN: sprite = new Sprite("Resources/Shotgun.png"); type = SHOTGUNITEM;  break;
	}
	BBox(new Rect(-22, -20, 22, 20));
	MoveTo(posX, posY);
	factor = -0.25f;
	
	timer.Start();
}

Itens::~Itens() {
	delete sprite;
}

void Itens::Update() {
	// aplica fator de escala
	Scale(1.0f + factor * gameTime);

	// amplia e reduz objeto
	if (scale < 0.85f)
		factor = 0.25f;
	if (scale > 1.00f)
		factor = -0.25f;

	if (timer.Elapsed(10.0f)) GeoWars::scene->Delete();

}

void Itens::Draw() {
	sprite->Draw(x, y, Layer::LOWER, 0.7f + scale);
}