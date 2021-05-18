#version 400

in vec2 uv;
in vec4 color;
in vec3 ReflectDir;

uniform sampler2D image;
uniform samplerCube cubemap; 
uniform bool DrawSkyBox; // Are we drawing the sky box?

out vec4 FragColor;

void main()
{
	// Access the cube map texture
	 vec4 cubeMapColor = texture(cubemap, ReflectDir);
	if(DrawSkyBox) {
		FragColor = cubeMapColor;
	} else {
		FragColor = color * texture(image, uv);	
	}
}
