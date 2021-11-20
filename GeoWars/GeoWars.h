/**********************************************************************************
// GeoWars (Arquivo de Cabeçalho)
//
// Criação:     23 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Demonstração da versão final do motor
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

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL, CURSOR, CONFIRM, CANCEL, APPLY };

// ------------------------------------------------------------------------------

class GeoWars : public Game
{
private:
	Background* backg = nullptr;   // pano de fundo
	Hud* hud = nullptr;            // painel de informações
	bool viewBBox = false;         // visualização das bouding boxes


public:
	static Guns		* gun;
	static Player	* player;			// nave controlada pela jogador
	static Audio	* audio;			// sitema de áudio
	static Scene	* scene;			// cena do jogo

	void Init();                    // inicialização
	void Update();                  // atualização
	void Draw();                    // desenho
	void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif