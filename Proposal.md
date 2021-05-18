# Particle Planetarium

## CS312 Final Project Proposal - Bryn Mawr College 2021

*A planetarium of animated stars, comets, and meteors with a space skybox cubemap as the background and a rotating (maybe, fly-through) camera.*

This project will be unique from other existing demos as it will simulate an animated shooting star/meteor/comet scene with multiple particles inside a skybox cubemap.
The camera will rotate around with the cursor (or maybe, fly through) to look around the whole scene.
Multiple particles/textures will be used:


- A skybox texture mapped onto a cubemap for an all-around background.

![skybox](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/skybox.png)


- A rock-like particle for the comet core/meteor that moves around the scene.

![meteor](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/meteor.png)


- An animated glowing comet tail that moves with the core and gets brighter or lighter each frame.
![glow](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/particle.png)

- Some Shooting stars
![blue-trail](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/blue-trail.png)


- Probably some randomly placed star particles that twinkle.

![stars](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/stars.png)


## Features planned and timeline for implementation:

*Minimum required*

5-10-2021 - Full sort to remove any black squares surrounding the particles

5-12-2021 - Skybox/Cubemap

5-15-2021 - Multiple texture support

5-17-2021 - A full-scene with animated shooting stars/meteors/comets

5-17-2021 - A rotating camera


*Good-to-have*

5-18-2021 - Randomly placed twinkling stars


*Stretch*

5-20-2021 - A fly-through camera


## Algorithms and Data Structures


*Full sort*

```
#include <algorithm>
.
.
.
// Sort the particles after they have been updated

std::sort(mParticles.begin(), mParticles.end()); //mParticles is the vector that stores the particles


// In Particle struct definition

bool operator<(const Particle& a) const
{
    float d1 = glm::distance(a.pos, a.cam_pos);
    float d2 = glm::distance(pos, cam_pos);
    return (d1 < d2);
}

```

*Skybox*

- Extend the classes and shaders used in Assignment 5 - particles.

- Extend the shader to support the skybox by adding uniform variables.

- Modify Renderer class to load the texture and draw the skybox.


*Supporting multiple particles/textures*

- Load each texture with a separate ID.

- Distinguish between the different textures while setting uniform variables in the shader.
