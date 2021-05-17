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
   mTexture1 = theRenderer.loadTexture("../textures/meteor.png");
   mTexture2 = theRenderer.loadTexture("../textures/blue-trail.png");
   //glEnable(GL_TEXTURE0);
   //float z_pos = -1.0f + ((float)i / size);
   //vec3 position = vec3(-4.0f, 4.0f, 0.0);
   vec3 position = vec3(0);
   //float x = random_float(1.0f, 5.0f);
   //float y = random_float(-5.0f, -1.0f);
   float x = 1.0f;
   float y = -1.0f;
   //vec3 velocity = vec3(x, y, 0.1);
   vec3 velocity = vec3(0);
   vec4 color = vec4(0.560f, 0.403f, 0.117f, 0.5f);
   float part_size = 4.0f;
   float mass = 4.0f;
   vec3 cam_pos = theRenderer.cameraPosition();

   Particle particle = { position, velocity, color, part_size, mass, cam_pos, mTexture1 };

   mParticles.push_back(particle);
   
   //glEnable(GL_TEXTURE2);
   //mTexture = theRenderer.loadTexture("../textures/blue-trail.png");
   position = vec3(0, 0, 1.0f);
   //x = 1.0f;
   //y = -1.0f;
   //velocity = vec3(x, y, 0.1);
   color = vec4(0.0f, 0.0f, 1.0f, 0.5f);
   part_size = 4.0f;
   mass = 4.0f;
   cam_pos = theRenderer.cameraPosition();

   particle = { position, velocity, color, part_size, mass, cam_pos, mTexture2 };

   mParticles.push_back(particle);
   /*
   for (int i = 0; i < size; i++)
   {
	   float z_pos = -1.0f + ((float)i / size);
	   vec3 position = vec3(0.0f, -1.0f, z_pos);
	   float x = random_float(-1.0f, 1.0f);
	   float y = abs(random_float(0.0f, 5.0f));
	   vec3 velocity = vec3(x, y, 0.1);
	   vec4 color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	   float part_size = 0.5f;
	   float mass = 2.0f;
	   vec3 cam_pos = theRenderer.cameraPosition();

	   Particle particle = { position, velocity, color, part_size, mass, cam_pos };

	   mParticles.push_back(particle);
   }*/
}

void Planetarium::update(float dt)
{
	vec3 cam_pos = theRenderer.cameraPosition();
	//glEnable(GL_TEXTURE0);
	Particle current_particle = mParticles[0];
	vec3 new_pos = current_particle.pos + current_particle.vel * dt;
	current_particle.pos = new_pos;
	mParticles[0] = current_particle;

	//glEnable(GL_TEXTURE2);
	current_particle = mParticles[1];
	new_pos = current_particle.pos + current_particle.vel * dt;
	current_particle.pos = new_pos;
	mParticles[1] = current_particle;
	/*
	for (int i = 0; i < mParticles.size(); i++)
	{
		Particle current_particle = mParticles[i];
		vec3 new_pos = current_particle.pos + current_particle.vel * dt;
		current_particle.size += 0.01;
		float alpha = current_particle.color.w;
		current_particle.color = vec4(1.0f, 0.0f, 0.0f, (alpha - 0.01f));


		if (new_pos.x > 2.5f || new_pos.x < -2.5f || new_pos.y > 2.5f)
		{ // Reuse particle
			float z_pos = -1.0f + ((float)i / mParticles.size());
			new_pos = vec3(0.0f, -1.0f, z_pos);
			current_particle.color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
			current_particle.size = 0.5f;
		}

		current_particle.pos = new_pos;
		mParticles[i] = current_particle;
	}*/
	std::sort(mParticles.begin(), mParticles.end());
	//std::sort(mParticles2.begin(), mParticles2.end());
}

