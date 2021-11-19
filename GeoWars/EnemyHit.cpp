#include "GeoWars.h"
#include "EnemyHit.h"


// ---------------------------------------------------------------------------------

EnemyHit::EnemyHit(float pX, float pY)
{
    // configura emissor de partículas
    Generator explosion;
    explosion.imgFile = "Resources/particle_min.png";    // arquivo de imagem
    explosion.angle = 0;                     // direção da explosão
    explosion.spread = 360.0f;                    // espalhamento em graus
    explosion.lifetime = 0.7f;                     // tempo de vida em segundos
    explosion.frequency = 0.000f;                   // tempo entre geração de novas partículas
    explosion.percentToDim = 0.6f;                  // desaparece após 60% da vida
    explosion.minSpeed = 25.0f;                    // velocidade mínima das partículas
    explosion.maxSpeed = 250.0f;                   // velocidade máxima das partículas
    explosion.color.r = 1.0f;                     // cor da partícula entre 0 e 1
    explosion.color.g = 0.5f;             // cor da partícula entre 0.64 e 1
    explosion.color.b = 0.0f;                     // cor da partícula entre 0 e 1
    explosion.color.a = 1.0f;                     // transparência da partícula

     // configura emissor de partículas
    Generator explosion2;
    explosion.imgFile = "Resources/particle_min.png";   
    explosion.angle = 0;                    
    explosion.spread = 360.0f;              
    explosion.lifetime = 0.7f;              
    explosion.frequency = 0.000f;           
    explosion.percentToDim = 0.5f;          
    explosion.minSpeed = 25.0f;             
    explosion.maxSpeed = 250.0f;            
    explosion.color.r = 1.0f;               
    explosion.color.g = 0.2;       
    explosion.color.b = 0.0f;               
    explosion.color.a = 1.0f;               

    // cria sistema de partículas
    particle1 = new Particles(explosion);
    particle2 = new Particles(explosion2);

    // gera 25 partículas na posição de contato
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
    // atualiza posição de cada partícula
    particle1->Update(gameTime);
    particle2->Update(gameTime);

    // remove da cena quando todas as partículas estão inativas
    if (particle1->Inactive())
        GeoWars::scene->Delete();
    if (particle2->Inactive())
        GeoWars::scene->Delete();
}

// -------------------------------------------------------------------------------