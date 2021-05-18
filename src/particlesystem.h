#ifndef ParticleSystem_H_
#define ParticleSystem_H_

#include "AGL.h"
#include "image.h"
#include "renderer.h"
#include <vector>

namespace agl {

   struct Particle {
      glm::vec3 pos;
      glm::vec3 vel;
      glm::vec4 color;
      float size;
      float mass;
      glm::vec3 cam_pos;
      GLuint texIf;
      
      bool operator<(const Particle& a) const
      {
          float d1 = glm::distance(a.pos, a.cam_pos);
          float d2 = glm::distance(pos, cam_pos);
          return (d1 < d2);
      }
   };

   class ParticleSystem {
   public:
      ParticleSystem();
      virtual ~ParticleSystem();

      void init(int size);
      virtual void update(float dt) = 0;
      virtual void draw();

      static Renderer& GetRenderer();
      
   protected:
      virtual void createParticles(int size) = 0;

   protected:

      std::vector<Particle> mParticles;
      GLuint mTexture1;
      GLuint mTexture2;
      GLuint mTexture3;
      BlendMode mBlendMode;
      static Renderer theRenderer;
   };
}
#endif