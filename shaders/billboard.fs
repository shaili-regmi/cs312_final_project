#version 420

in vec2 uv;
in vec4 color;
in vec3 ReflectDir;

layout(binding = 0) uniform sampler2D meteor;
layout(binding = 2) uniform sampler2D trail;
uniform samplerCube cubemap; 
uniform bool DrawSkyBox; // Are we drawing the sky box?
uniform bool DrawMeteor;
uniform bool DrawTrail;

out vec4 FragColor;

void main()
{
	// Access the cube map texture
	 vec4 cubeMapColor = texture(cubemap, ReflectDir);
	if(DrawSkyBox) {
		FragColor = cubeMapColor;
	} else {

		if (DrawTrail)
		{ 
			FragColor = color * texture(trail, uv);
		} else {
			FragColor = color * texture(meteor, uv);
		}
		//FragColor = mix(texture(meteor, uv), texture(trail, uv), 0.2);
	}
}
