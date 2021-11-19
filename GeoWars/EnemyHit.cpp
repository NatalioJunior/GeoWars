#include "GeoWars.h"
#include "EnemyHit.h"


// ---------------------------------------------------------------------------------

EnemyHit::EnemyHit(float pX, float pY)
{
    // configura emissor de part�culas
    Generator explosion;
    explosion.imgFile = "Resources/particle_min.png";    // arquivo de imagem
    explosion.angle = 0;                     // dire��o da explos�o
    explosion.spread = 360.0f;                    // espalhamento em graus
    explosion.lifetime = 0.7f;                     // tempo de vida em segundos
    explosion.frequency = 0.000f;                   // tempo entre gera��o de novas part�culas
    explosion.percentToDim = 0.6f;                  // desaparece ap�s 60% da vida
    explosion.minSpeed = 25.0f;                    // velocidade m�nima das part�culas
    explosion.maxSpeed = 250.0f;                   // velocidade m�xima das part�culas
    explosion.color.r = 1.0f;                     // cor da part�cula entre 0 e 1
    explosion.color.g = 0.5f;             // cor da part�cula entre 0.64 e 1
    explosion.color.b = 0.0f;                     // cor da part�cula entre 0 e 1
    explosion.color.a = 1.0f;                     // transpar�ncia da part�cula

     // configura emissor de part�culas
    Generator explosion2;
    explosion2.imgFile = "Resources/particle_min.png";   
    explosion2.angle = 0;                    
    explosion2.spread = 360.0f;              
    explosion2.lifetime = 0.7f;              
    explosion2.frequency = 0.000f;           
    explosion2.percentToDim = 0.5f;          
    explosion2.minSpeed = 25.0f;             
    explosion2.maxSpeed = 250.0f;            
    explosion2.color.r = 1.0f;               
    explosion2.color.g = 0.2f;       
    explosion2.color.b = 0.0f;               
    explosion2.color.a = 1.0f;               

    // cria sistema de part�culas
    particle1 = new Particles(explosion);
    particle2 = new Particles(explosion2);

    // gera 25 part�culas na posi��o de contato
    particle1->Generate(pX, pY, 25);
    particle2->Generate(pX, pY, 10);
    type = HIT;
}

// ---------------------------------------------------------------------------------

EnemyHit::~EnemyHit()
{
    delete particle1;
    delete particle2;
}

// -------------------------------------------------------------------------------

void EnemyHit::Update()
{
    // atualiza posi��o de cada part�cula
    particle1->Update(gameTime);
    particle2->Update(gameTime);

    // remove da cena quando todas as part�culas est�o inativas
    if (particle1->Inactive())
        GeoWars::scene->Delete();
    if (particle2->Inactive())
        GeoWars::scene->Delete();
}

// -------------------------------------------------------------------------------