// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "confetti.h"
#include <algorithm>

using namespace std;
using namespace agl;
using namespace glm;

void Confetti::createParticles(int size) 
{
   mTexture = theRenderer.loadTexture("../textures/particle.png");
   
   // TODO: Create particles

   for (int i = 0; i < size; i++)
   {
	   vec3 position = random_unit_cube();
	   vec3 velocity = vec3(random_float(-2.0f, 2.0f), random_float(-2.0f, 2.0f), random_float(-2.0f, 2.0f));
	   vec4 color = vec4(random_float(0.0f, 1.0f), random_float(0.0f, 1.0f), random_float(0.0f, 1.0f), 1.0f);
	   float part_size = 0.25f;
	   float mass = 1.0f;
	   vec3 cam_pos = theRenderer.cameraPosition();

	   Particle particle = { position, velocity, color, part_size, mass, cam_pos };

	   mParticles.push_back(particle);
   }
}

void Confetti::update(float dt)
{
	// update particles
	vec3 cam_pos = theRenderer.cameraPosition();

	for (int i = 0; i < mParticles.size(); i++)
	{
		Particle current_particle = mParticles[i];
		vec3 current_vel = current_particle.vel;

		vec3 new_pos = current_particle.pos + current_vel * dt;

		if (new_pos.x > 1.0f || new_pos.x < -1.0f)
		{
			current_vel.x = -1.0f * current_vel.x;
			new_pos = current_particle.pos + current_vel * dt;
		}
		if (new_pos.y > 1.0f || new_pos.y < -1.0f)
		{
			current_vel.y = -1.0f * current_vel.y;
			new_pos = current_particle.pos + current_vel * dt;
		}
		if (new_pos.z > 1.0f || new_pos.z < -1.0f)
		{
			current_vel.z = -1.0f * current_vel.z;
			new_pos = current_particle.pos + current_vel * dt;
		}

		current_particle.pos = new_pos;
		current_particle.vel = current_vel;
		mParticles[i] = current_particle;
	}
	std::sort(mParticles.begin(), mParticles.end());
}


