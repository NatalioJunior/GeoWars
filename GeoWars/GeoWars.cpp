/**********************************************************************************
// GeoWars (C?digo Fonte)
//
// Cria??o:     23 Out 2012
// Atualiza??o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri??o:   Demonstra??o da vers?o final do motor
//
**********************************************************************************/

#include "Resources.h"
#include "GeoWars.h"
#include "Engine.h"
#include "Delay.h"
#include "MiniBossLarryTank.h"

// ------------------------------------------------------------------------------

Player* GeoWars::player = nullptr;
Audio* GeoWars::audio = nullptr;
Scene* GeoWars::scene = nullptr;
Guns* GeoWars::gun = nullptr;

int GeoWars::nSoldier = 0;
int GeoWars::nBlue = 0;
int GeoWars::nOrange = 0;
int GeoWars::nMagenta = 0;
int GeoWars::nGreen = 0;
int GeoWars::nMiniboss = 0;
int GeoWars::nSpawners = 0;

bool GeoWars::bossOn = 0;
bool GeoWars::spawnOn = 1;

int GeoWars::worldDifficulty = 1;
// ------------------------------------------------------------------------------

void GeoWars::Init()
{
	// cria sistema de ?udio
	audio = new Audio();
	audio->Add(THEME, "Resources/Theme.wav");
	audio->Add(FIRE, "Resources/Fire.wav", 18);
	audio->Add(HITWALL, "Resources/Hitwall.wav", 5);
	audio->Add(EXPLODE, "Resources/Explode.wav");
	audio->Add(START, "Resources/Start.wav");
	audio->Add(CURSOR, "Resources/CursorMove.wav", 7);
	audio->Add(CONFIRM, "Resources/Confirm.wav");
	audio->Add(CANCEL, "Resources/Cancel.wav");
	audio->Add(APPLY, "Resources/Apply.wav");
	audio->Add(POP, "Resources/Pop.wav", 3);
	audio->Add(HEAVY, "Resources/HeavyMachineGun.wav");
	audio->Add(SHOTGUN, "Resources/Shotgun.wav");

	audio->Volume(HITWALL, 0.25f);

	// carrega/incializa objetos
	backg = new Background("Resources/Arena.jpg");
	player = new Player();
	gun = new Guns();
	scene = new Scene();
	player->gun = gun;

	// cria o painel de informa??es
	hud = new Hud();

	const int size1 = 9;
	Instruction larryScriptTest1[size1] =
	{
	{ MOVETO, 340.0f, 0.0f, 5.0f },
	{ MOVETO, 50.0f, 320.0f, 5.0f },
	{ ROTATE, 5.0f, 8.0f, 0.8f },
	{ MOVE, 90.0f, 5.0f, 0.5f },
	{ MOVETO, 300.0f, 100.0f, 5.0f },
	{ MOVE, 270.0f, 0.0f, 1.0f },
	{ SLIDE, 180.0f, 0.5f, 5.0f },
	{ SLIDE, 0.0f, 0.5f, 5.0f },
	{ JUMP, 6.0f, 0.0f, 0.0f }
	};
	//scene->Add(new MiniBossLarryTank(larryScriptTest1,size1,1500,1500),MOVING);

	//scene->Add(new Delay(), STATIC);

	// ----------------------
	// inicializa a viewport
	// ----------------------

	// calcula posi??o para manter viewport centralizada
	float difx = (game->Width() - window->Width()) / 2.0f;
	float dify = (game->Height() - window->Height()) / 2.0f;

	// inicializa viewport para o centro do mundo
	viewport.left = 0.0f + difx;
	viewport.right = viewport.left + window->Width();
	viewport.top = 0.0f + dify;
	viewport.bottom = viewport.top + window->Height();
}

// ------------------------------------------------------------------------------

void GeoWars::Update()
{
	// sai com o pressionamento da tecla ESC
	if (window->KeyDown(VK_ESCAPE))
		window->Close();

	// atualiza cena e calcula colis?es
	scene->Update();
	scene->CollisionDetection();

	// ativa ou desativa a bounding box
	if (window->KeyPress('B'))
		viewBBox = !viewBBox;

	// --------------------
	// atualiza a viewport
	// --------------------

	viewport.left = player->X() - window->CenterX();
	viewport.right = player->X() + window->CenterX();
	viewport.top = player->Y() - window->CenterY();
	viewport.bottom = player->Y() + window->CenterY();

	if (viewport.left < 0)
	{
		viewport.left = 0;
		viewport.right = window->Width();
	}
	else if (viewport.right > game->Width())
	{
		viewport.left = game->Width() - window->Width();
		viewport.right = game->Width();
	}

	if (viewport.top < 0)
	{
		viewport.top = 0;
		viewport.bottom = window->Height();
	}
	else if (viewport.bottom > game->Height())
	{
		viewport.top = game->Height() - window->Height();
		viewport.bottom = game->Height();
	}

	hud->Update();

	if (player->defeat) {
		scene->Remove(player, MOVING);
		scene->Remove(gun, STATIC);
		delete scene;
		scene = new Scene();
		audio->Stop(THEME);
	}
}

// ------------------------------------------------------------------------------

void GeoWars::Draw()
{
	// desenha pano de fundo
	backg->Draw(viewport);

	// desenha a cena
	scene->Draw();

	hud->Draw();

	// desenha bounding box
	if (viewBBox)
		scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void GeoWars::Finalize()
{
	delete audio;
	delete backg;
	scene->Remove(player, MOVING);
	scene->Remove(gun, STATIC);
	delete player;
	delete gun;
	delete hud;
	delete scene;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// cria motor do jogo
	Engine* engine = new Engine();

	// configura motor
	//engine->window->Mode(WINDOWED);
	//engine->window->Size(1728, 972);
	engine->window->Mode(BORDERLESS);
	engine->window->Color(0, 0, 0);
	engine->window->Title("GeoWars");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);
	//engine->window->HideCursor(false);
	engine->graphics->VSync(false);

	// cria o jogo
	Game* game = new GeoWars();

	// configura o jogo
	game->Size(3840, 2160);

	// inicia execu??o
	int status = engine->Start(game);

	// destr?i motor e encerra jogo
	delete engine;
	return status;
}

// ----------------------------------------------------------------------------