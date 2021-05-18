// Shaili Regmi
// CS312 - Final Project
// Particle Planetarium
// Base Code: Bryn Mawr College, alinen, 2020

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "planetarium.h"

using namespace std;
using namespace agl;
using namespace glm;

void Planetarium::createParticles(int size) 
{
   mBlendMode = ALPHA;
   mTexture1 = theRenderer.loadTexture("../textures/blue-trail.png");
   mTexture2 = theRenderer.loadTexture("../textures/stars-rescale.png");
   mTexture3 = theRenderer.loadTexture("../textures/meteor.png");

   for (int i = 0; i < size; i++)
   {
	   float x_pos = -5.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.0f - (-5.0f))));
	   float y_pos = 1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5.0f - (1.0f))));
	   float z_pos = -3.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.0f - (-3.0f))));

	   vec3 position = vec3(x_pos, y_pos, z_pos);
	   vec3 velocity = vec3(1.0f, -1.0f, 0.0f);
	   vec4 color = vec4(0.474f, 0.749f, 0.843f, 1.0f);
	   float part_size = 3.0f;
	   float mass = 3.0f;
	   vec3 cam_pos = theRenderer.cameraPosition();

	   Particle particle = { position, velocity, color, part_size, mass, cam_pos, mTexture1 };
	   mParticles.push_back(particle);

	   x_pos = -5.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.0f - (-5.0f))));
	   y_pos = 1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5.0f - (1.0f))));
	   z_pos = -3.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.0f - (-3.0f))));

	   position = vec3(x_pos, y_pos, z_pos);
	   velocity = vec3(1.0f, -1.0f, 0.0f);
	   color = vec4(0.560f, 0.403f, 0.117f, 1.0f);
	   part_size = 3.0f;
	   mass = 3.0f;
	   cam_pos = theRenderer.cameraPosition();

	   particle = { position, velocity, color, part_size, mass, cam_pos, mTexture3 };
	   mParticles.push_back(particle);

	   x_pos = -4.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4.0f - (-4.0f))));
	   y_pos = -4.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4.0f - (-4.0f))));
	   z_pos = -2.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f - (-2.0f))));

	   position = vec3(x_pos, y_pos, z_pos);
	   velocity = vec3(0);
	   color = vec4(1);
	   part_size = 3.0f;
	   mass = 3.0f;
	   cam_pos = theRenderer.cameraPosition();

	   particle = { position, velocity, color, part_size, mass, cam_pos, mTexture2 };
	   mParticles.push_back(particle);

	   position = vec3(-x_pos, -y_pos, -z_pos);
	   particle = { position, velocity, color, part_size, mass, cam_pos, mTexture2 };
	   mParticles.push_back(particle);
   }
}

void Planetarium::update(float dt)
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		Particle current_particle = mParticles[i];
		if (current_particle.texIf == mTexture1 || current_particle.texIf == mTexture3)
		{
			vec3 new_pos = current_particle.pos + current_particle.vel * dt;

			//Reuse particles
			if (new_pos.x > 5.0f || new_pos.y < -5.0f || new_pos.z > 2.5f)
			{
				float x_pos = -5.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.0f - (-5.0f))));
				float y_pos = 1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5.0f - (1.0f))));
				float z_pos = -3.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.0f - (-3.0f))));

				new_pos = vec3(x_pos, y_pos, z_pos);
			}
			current_particle.pos = new_pos;
			vec3 cam_pos = theRenderer.cameraPosition();
			current_particle.cam_pos = cam_pos;
			mParticles[i] = current_particle;
		}
		else if (current_particle.texIf == mTexture2)
		{
			float current_w = current_particle.color.w;
			float new_w = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			while (new_w == current_w)
			{
				new_w = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			}
			vec4 color = vec4(1.0f, 1.0f, 1.0f, new_w);
			current_particle.color = color;
			vec3 cam_pos = theRenderer.cameraPosition();
			current_particle.cam_pos = cam_pos;
			mParticles[i] = current_particle;
		}
	}

	std::sort(mParticles.begin(), mParticles.end());
}

