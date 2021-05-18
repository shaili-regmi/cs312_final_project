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
   mTexture3 = -1;
}

ParticleSystem::~ParticleSystem()
{
    mParticles.clear();
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
}