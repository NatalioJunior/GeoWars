#include "LevelControll.h"
#include "GeoWars.h"
#include "MiniBossLarryTank.h"
#include "SpawnerA.h"
#include "SpawnerB.h"
#include "SpawnerC.h"
#include "SpawnerD.h"
// ------------------------------------------------------------------------------

LevelControll::LevelControll() :spawnerApX(230, 799), spawnerApY(230, 500), spawnerBpX(3000, 3600), spawnerBpY(230, 500), spawnerCpX(230, 799), spawnerCpY(1400, 1600), spawnerDpX(3000, 3600), spawnerDpY(1400, 1600),
bossScript(1, 2)
{
	//spawnerApX
	//spawnerApY
	//spawnerBpX
	//spawnerBpY
	//spawnerCpX
	//spawnerCpY
	//spawnerDpX
	//spawnerDpY
}

// ------------------------------------------------------------------------------

LevelControll::~LevelControll()
{
}

// -------------------------------------------------------------------------------

void LevelControll::Update()
{
	if (GeoWars::nMiniboss == 0 && GeoWars::bossOn) {
		GeoWars::worldDifficulty += 1;
		GeoWars::bossOn = false;
		GeoWars::spawnOn = true;
		GeoWars::scene->Add(new SpawnerA(spawnerApX.Rand(), spawnerApY.Rand(), 0.0f, 2.0f), MOVING);
		GeoWars::scene->Add(new SpawnerB(spawnerBpX.Rand(), spawnerBpY.Rand(), 180.0f, 2.0f), MOVING);
		GeoWars::scene->Add(new SpawnerC(spawnerCpX.Rand(), spawnerCpY.Rand(), 0.0f, 2.0f), MOVING);
		GeoWars::scene->Add(new SpawnerD(spawnerDpX.Rand(), spawnerDpY.Rand(), 180.0f, 2.0f), MOVING);
		//timer.Reset();
	}

	if (GeoWars::nSpawners <= 0 && GeoWars::spawnOn) {
		GeoWars::bossOn = true;
		GeoWars::spawnOn = false;
		//timer.Start();


		const int size1 = 12;
		Instruction larryScriptTest1[size1] =
		{
		{ MOVETO, 500.0f, 300.0f, 5.0f },
		{ MOVETO, 1000.0f, 420.0f, 5.0f },
		{ SHOOT_THREE, 0.0f, 0.0f,0.0f},
		{ ROTATE, 5.0f, 8.0f, 0.8f },
		{ MOVE, 60.0f, 40.0f, 1.5f },
		{ MOVETO, GeoWars::player->X(), GeoWars::player->Y(), 5.0f },
		{ MOVE, 700.0f, 0.0f, 1.0f },
		{ SLIDE, 170.0f, 0.5f, 5.0f },
		{ SHOOT_THREE, 0.0f, 0.0f, 0.0f},
		{ SLIDE, 0.0f, 0.5f, 5.0f },
		{ MOVETO, GeoWars::player->X(), GeoWars::player->Y(), 5.0f },
		{ JUMP, 6.0f, 0.0f, 0.0f }
		};
		const int size2 = 12;
		Instruction script2[size2] =
		{
		{ MOVETO, 1000.0f, 1200.0f, 5.0f },
		{ MOVETO, 3000.0f, 420.0f, 5.0f },
		{ SHOOT_THREE, 0.0f, 0.0f,0.0f},
		{ ROTATE, 5.0f, 8.0f, 0.8f },
		{ MOVE, 50.0f, 40.0f, 1.5f },
		{ MOVETO, GeoWars::player->X(), GeoWars::player->Y(), 5.0f },
		{ MOVE, 700.0f, 400.0f, 1.0f },
		{ SLIDE, 180.0f, 0.5f, 5.0f },
		{ SHOOT_THREE, 0.0f, 0.0f, 0.0f},
		{ SLIDE, 0.0f, 0.5f, 5.0f },
		{ MOVETO, GeoWars::player->X(), GeoWars::player->Y(), 5.0f },
		{ JUMP, 6.0f, 0.0f, 0.0f }
		};
		//GeoWars::scene->Add(new MiniBossLarryTank(larryScriptTest1, size1, 1500, 1500), MOVING);

		switch (bossScript.Rand())
		{
		case 1 :
			GeoWars::scene->Add(new MiniBossLarryTank(larryScriptTest1, size1, 1500, 1500), MOVING);
			break;

		case 2:
			GeoWars::scene->Add(new MiniBossLarryTank(script2, size2, 1500, 1500), MOVING);
			break;
		default:
			GeoWars::scene->Add(new MiniBossLarryTank(larryScriptTest1, size1, 1500, 1500), MOVING);
			break;
		}

		//timer.Stop();

	}
	//if (timer.Elapsed() == 5) {
	//}
}

void LevelControll::Draw() {

}
// -------------------------------------------------------------------------------
