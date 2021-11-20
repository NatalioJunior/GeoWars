/**********************************************************************************
// GeoWars (Arquivo de Cabe�alho)
//
// Cria��o:     23 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Demonstra��o da vers�o final do motor
//
**********************************************************************************/

#ifndef _GEOWARS_H_
#define _GEOWARS_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "Hud.h"
#include "Guns.h"

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, BLUE, GREEN, MAGENTA, ORANGE, WALLHIT, SOLDIER, MINI_BOSS, SPAWNER, HIT, ENMEY_PROJECTILE };

// ------------------------------------------------------------------------------

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL, CURSOR, CONFIRM };

// ------------------------------------------------------------------------------

class GeoWars : public Game
{
private:
	Background* backg = nullptr;   // pano de fundo
	Hud* hud = nullptr;            // painel de informa��es
	bool viewBBox = false;         // visualiza��o das bouding boxes


public:
	static Guns		* gun;
	static Player	* player;			// nave controlada pela jogador
	static Audio	* audio;			// sitema de �udio
	static Scene	* scene;			// cena do jogo
	static bool		viewHUD;			// visualiza��o do painel

	void Init();                    // inicializa��o
	void Update();                  // atualiza��o
	void Draw();                    // desenho
	void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif