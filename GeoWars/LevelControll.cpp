#include "LevelControll.h"
#include "GeoWars.h"
#include "MiniBossLarryTank.h"
#include "SpawnerA.h"
#include "SpawnerB.h"
#include "SpawnerC.h"
#include "SpawnerD.h"
// ------------------------------------------------------------------------------

LevelControll::LevelControll()
{
	
}

// ------------------------------------------------------------------------------

LevelControll::~LevelControll()
{
}

// -------------------------------------------------------------------------------

void LevelControll::Update()
{
	if (GeoWars::nMiniboss == 0) {
	}

	if (GeoWars::nSpawners <= 0) {
		
		//timer.Start();
		
		/*
		const int size1 = 11;
		Instruction larryScriptTest1[size1] =
		{
		{ MOVETO, 500.0f, 300.0f, 5.0f },
		{ MOVETO, 1000.0f, 1320.0f, 5.0f },
		{ SHOOT_THREE, 0.0f, 0.0f,0.0f},
		{ ROTATE, 5.0f, 8.0f, 0.8f },
		{ MOVE, 600.0f, 40.0f, 1.5f },
		{ MOVETO, 23000.0f, 500.0f, 5.0f },
		{ MOVE, 270.0f, 0.0f, 1.0f },
		{ SLIDE, 180.0f, 0.5f, 5.0f },
		{ SHOOT_THREE, 0.0f, 0.0f, 0.0f},
		{ SLIDE, 0.0f, 0.5f, 5.0f },
		{ JUMP, 6.0f, 0.0f, 0.0f }
		};
		GeoWars::scene->Add(new MiniBossLarryTank(larryScriptTest1, size1, 1500, 1500), MOVING);
		*/
		GeoWars::worldDifficulty += 10;

		GeoWars::scene->Add(new SpawnerA(230, 230, 0, 2), MOVING);
		GeoWars::scene->Add(new SpawnerB(2000, 230, 180, 2), MOVING);
		GeoWars::scene->Add(new SpawnerC(230, 1600, 0, 2), MOVING);
		GeoWars::scene->Add(new SpawnerD(2000, 1500, 180, 2), MOVING);
		timer.Reset();
		timer.Stop();
		
	}
	//if (timer.Elapsed() == 5) {
	//}
	
}

void LevelControll::Draw() {

}
// -------------------------------------------------------------------------------
