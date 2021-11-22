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

	RandI spawnerApX;
	RandI spawnerApY;
	RandI spawnerBpX;
	RandI spawnerBpY;
	RandI spawnerCpX;
	RandI spawnerCpY;
	RandI spawnerDpX;
	RandI spawnerDpY;
public:
	LevelControll();        // construtor
	~LevelControll();                         // destrutor

	void Update();                      // atualização
	void Draw();                        // desenho
};
#endif