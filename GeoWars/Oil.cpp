#include "Oil.h"
#include "GeoWars.h"

// ------------------------------------------------------------------------------

Oil::Oil(float pX, float pY)
{
	sprite = new Sprite("Resources/Oil.png");
	MoveTo(pX, pY);

	Point vertex[42] =
	{
		Point(0.0f,-100.0f), Point(13.0f,-100.0f), Point(30.0f,-85.0f), Point(35.0f, -65.0f),
		Point(50.0f,-80.0f), Point(65.0f,-70.0f), Point(60.0f,-55.0f), Point(63.0f, -43.0f),
		Point(55.0f,-30.0f), Point(95.0f,-20.0f), Point(100.0f,0.0f), Point(77.0f, 9.0f),
		Point(60.0f,20.0f), Point(65.0f,45.0f), Point(50.0f,50.0f), Point(50.0f, 60.0f),
		Point(50.0f,80.0f), Point(30.0f,85.0f), Point(20.0f,60.0f), Point(15.0f, 55.0f),
		Point(15.0f,70.0f), Point(5.0f,80.0f), Point(0.0f,100.0f), Point(-10.0f, 100.0f),
		Point(-25.0f,80.0f), Point(-35.0f,60.0f), Point(-55.0f,70.0f), Point(-65.0f, 55.0f),
		Point(-60.0f,30.0f), Point(-90.0f,40.0f), Point(-100.0f,20.0f), Point(-80.0f, 5.0f),
		Point(-70.0f,0.0f), Point(-85.0f,-30.0f), Point(-65.0f,-40.0f), Point(-50.0f, -35.0f),
		Point(-50.0f,-60.0f), Point(-50.0f,-90.0f), Point(-35.0f,-90.0f), Point(-25.0f, -65.0f),
		Point(-10.0f,-65.0f), Point(-10.0f,-90.0f)
	};
	BBox(new Poly(vertex, 42));
	type = OIL;
}

// ------------------------------------------------------------------------------

Oil::~Oil()
{
	delete sprite;
}

// -------------------------------------------------------------------------------

void Oil::Update()
{
}

void Oil::Draw() {
	sprite->Draw(x, y, Layer::LOWER);
}
// -------------------------------------------------------------------------------
