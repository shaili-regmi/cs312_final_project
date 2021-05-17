#include "particlesystem.h"
#include "AGLM.h"

using namespace glm;
using namespace std;
using namespace agl;

Renderer ParticleSystem::theRenderer;

Renderer& ParticleSystem::GetRenderer()
{
   return theRenderer;
}

ParticleSystem::ParticleSystem()
{
   mBlendMode = ADD;
   mTexture1 = -1;
   mTexture2 = -1;
}

ParticleSystem::~ParticleSystem()
{
    mParticles.clear();
    //mParticles2.clear();
}

void ParticleSystem::init(int size)
{
   if (!theRenderer.initialized())
   {
      theRenderer.init("../shaders/billboard.vs", "../shaders/billboard.fs");
   }
   createParticles(size);
}

void ParticleSystem::draw() 
{
    for (int i = 0; i < mParticles.size(); i++)
    {
        Particle particle = mParticles[i];
        theRenderer.begin(particle.texIf, mBlendMode);
        theRenderer.quad(particle.pos, particle.color, particle.size);
    }
    /*
   theRenderer.begin(mTexture1, mBlendMode);
   for (int i = 0; i < mParticles1.size(); i++)
   {
      Particle particle = mParticles1[i];
      theRenderer.quad(particle.pos, particle.color, particle.size);
   }

   theRenderer.begin(mTexture2, mBlendMode);
   for (int i = 0; i < mParticles2.size(); i++)
   {
       Particle particle = mParticles2[i];
       theRenderer.quad(particle.pos, particle.color, particle.size);
   }
   */
}