#ifndef _PLATANK_LEVELCONTROLL_H_
#define _PLATANK_LEVELCONTROLL_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Animation.h"
#include "TileSet.h"
#include "Timer.h"
#include "Random.h"
// ---------------------------------------------------------------------------------

class LevelControll : public Object
{
private:
	Timer timer;

	RandF spawnerApX;
	RandF spawnerApY;
	RandF spawnerBpX;
	RandF spawnerBpY;
	RandF spawnerCpX;
	RandF spawnerCpY;
	RandF spawnerDpX;
	RandF spawnerDpY;
public:
	LevelControll();        // construtor
	~LevelControll();                         // destrutor

	void Update();                      // atualização
	void Draw();                        // desenho
};
#endif