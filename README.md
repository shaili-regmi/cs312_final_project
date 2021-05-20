# Particle Planetarium

## cs312_final_project - Bryn Mawr College Spring 2021

The demo of a planetarium using particle systems implemented using openGL.

## How to build and run

*Same as Assignment 5 - particles*

Open git bash to the directory containing this repository (cs312_final_project).

```
cs312_final_project $ mkdir build
cs312_final_project $ cd build
cs312_final_project/build $ cmake -G "Visual Studio 16 2019" ..
cs312_final_project/build $ start CS312-Final_Project.sln
```

Your solution file should contain one project: `planetarium`.
To run from the git bash command shell, 

```
cs312_final_project/build $ ../bin/Debug/planetarium

```

*macOS*

Open terminal to the directory containing this repository (cs312_final_project).

```
cs312_final_project $ mkdir build
cs312_final_project $ cd build
cs312_final_project/build $ cmake ..
cs312_final_project/build $ make
```

To run each program from build, you would type

```
cs312_final_project/build $ ../bin/planetarium

```

*Note: All the textures used are in the textures directory in this repository, the thumbnails used in this README are in the thumbnails directory, and all the demo videos are in the demos directory as well as on vimeo.com (links below).*


# Planetarium using Particles

[!Planetarium](https://github.com/shaili-regmi/cs312_final_project/blob/main/thumbnails/planetarium.png)


*A planetarium of twinkling and shooting stars and a glowing meteor with a space skybox cubemap as the background and a rotating camera.*

The camera rotates around with the left mouse button click and cursor position to look around the whole scene.
Multiple particles/textures are used:


- A skybox texture mapped onto a cubemap for an all-around background.

![skybox](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/skybox.png)


- A rock-like particle for the meteor core.

![meteor](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/meteor.png)


- An animated glowing meteor tail that moves with the core and gets brighter or lighter each frame.

![glow](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/particle.png)


- Some Shooting stars

![blue-trail](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/blue-trail.png)


- Randomly placed star that twinkle.

![stars](https://github.com/shaili-regmi/cs312_final_project/blob/main/textures/stars.png)


## Algorithms and Data Structures


*Rotating Camera*

- Same as Assignment 4 - mesh viewer

- The camera rotates around with the left mouse button click and the cursor position determines the rotation angles.

- Rotates horizontally around the Y axis and elevates vertically around the XZ plane.

- Rotation limited to -180 to 180 degrees in the x-direction and -90 to 90 degrees in the y-direction.

- Implemented using polar coordinates (Azimuth/rotation around the Y axis, Elevation/vertical rotation, and dist/distance from the origin) such that at any frame, the camera is looking from the coordinates:

```

x = Dist * sin(Azimuth) * cos(Elevation)
y = Dist * sin(Elevation)
z = Dist * cos(Azimuth) * cos(Elevation)

```


*Skybox*

- A sky texture mapped onto a cube to show an all-around background when camera is inside the cube.

- Existing implementation used - Skybox.h and Skybox.cpp

- Extended the classes and shaders used in Assignment 5 - particles.

- Extended the shader to support the skybox by adding uniform variables.

- Modified Renderer class to draw the cubemap/skybox.

- With hard-coded color (no texture):

[![Cubemap](https://github.com/shaili-regmi/cs312_final_project/blob/main/thumbnails/cubemap.png)](https://vimeo.com/552192845 "Cubemap")

- Modified Renderer class to load the skybox texture with an ID separate from that used for the particle textures.

- Distinguished between the different textures in the shader by setting uniform variables (a cubemap and a boolean variable).

- The six texture images (one for each face of the cube) loaded in the correct order and orientation with respect to the code by trial-and-error.

- Skybox from a distance:

[![Skybox-Distance](https://github.com/shaili-regmi/cs312_final_project/blob/main/thumbnails/skybox%20out.png)](https://vimeo.com/552192903 "Skybox from a distance")

- With Camera inside the skybox:

[![Skybox](https://github.com/shaili-regmi/cs312_final_project/blob/main/thumbnails/skybox%20in.png)](https://vimeo.com/552192912 "Skybox background")


*Full sort*

- The vector list containing the particles sorted so that there is no black box around the particles and that no particle blocks another particle from the camera view.

- The std::sort under <algorithm> header used for a fast O(n log n) sort.

- Defined the less-than (<) operator for the particle struct so that each particle knows what order it should be in with respect to other particles.

```
#include <algorithm>
.
.
.
// Sort the particles after they have been updated

std::sort(mParticles.begin(), mParticles.end()); //mParticles is the vector that stores the particles


// In Particle struct definition

glm::vec3 cam_pos; // Current camera position passed as a member variable

bool operator<(const Particle& a) const
{
    float d1 = glm::distance(a.pos, a.cam_pos);
    float d2 = glm::distance(pos, cam_pos);
    return (d1 < d2);
}

```


*Supporting multiple textures for Particles*

- Modified ParticleSystem class to store separate IDs for each texture used as member variables.

- Modified Particle struct to store the texture ID for each particle.

- All particles, no matter which texture they use, stored in the same list – helps in sorting them with respect to each other.


## Individual Demos


*Glowing Meteor:*

- Animated using two different particles - one for the core and another for the tail.

- The two particles move together from the top left of the screen to the bottom right (with respect to 0 rotation of the camera).

- Particles reused after they reach approximately out of the screen. Spawned at the original position.

- The glowing tail animated by changing the alpha value of the color to a random number between 0 and 1 each frame.

[![Glowing Meteor](https://github.com/shaili-regmi/cs312_final_project/blob/main/thumbnails/meteor%20and%20glow.png)](https://vimeo.com/552192851 "Glowing Meteor")


*Shooting Stars:*

- The shooting star textures move from the top left of the screen to the bottom right (with respect to 0 rotation of the camera).

- Particles reused after they reach approximately out of the screen. Spawned at a random position around the top left of the screen.

[![Shooting Stars](https://github.com/shaili-regmi/cs312_final_project/blob/main/thumbnails/shooting%20stars.png)](https://vimeo.com/552192893 "Shooting Stars")


*Twinkling Stars:*

- Randomly placed group of stars texture.

- Animated by changing the alpha value of the color to a random number between 0 and 1 each frame to give the twinkling effect.

[![Twinkling Stars](https://github.com/shaili-regmi/cs312_final_project/blob/main/thumbnails/stars.png)](https://vimeo.com/552192961 "Twinkling Stars")


## Putting it all together


[![Planetarium Closeup](https://github.com/shaili-regmi/cs312_final_project/blob/main/thumbnails/planetarium-closeup.png)](https://vimeo.com/552841681 "Planetarium Closeup")


[![Particle Planetarium](https://github.com/shaili-regmi/cs312_final_project/blob/main/thumbnails/planetarium.png)](https://vimeo.com/552841803 "Particle Planetarium")


## Future Directions

- Rotate the billboard that the particles are on around the z-axis so that the shooting stars and meteors look like they are moving in different directions (instead of just top left to bottom right).

- Animate each element (shooting star or meteor) using multiple smaller particles for the same element to get a more 3D-like animation effect when the camera rotates.

- Implement a fly-through camera to look at the scene from a more 3D perspective.










