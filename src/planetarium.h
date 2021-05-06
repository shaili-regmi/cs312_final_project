#ifndef Planetarium_H_
#define Planetarium_H_

#include "particlesystem.h"

namespace agl {

   class Planetarium : public ParticleSystem {
   public:
      virtual void createParticles(int size) override;
      virtual void update(float dt) override;
   };
}
#endif
