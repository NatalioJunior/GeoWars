#ifndef _PLATANK_LEVELCONTROLL_H_
#define _PLATANK_LEVELCONTROLL_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Animation.h"
#include "TileSet.h"
#include "Timer.h"
// ---------------------------------------------------------------------------------

class LevelControll : public Object
{
private:
	Timer timer;
public:
	LevelControll();        // construtor
	~LevelControll();                         // destrutor

	void Update();                      // atualização
	void Draw();                        // desenho
};
#endif