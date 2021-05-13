#version 400

in vec2 uv;
in vec4 color;
in vec3 ReflectDir;

uniform sampler2D image;
uniform samplerCube cubemap; 
uniform bool DrawSkyBox; // Are we drawing the sky box?
//uniform float ReflectFactor; // Amount of reflection
//uniform vec4 MaterialColor; // Color of the object's "Tint"

out vec4 FragColor;

void main()
{
	// Access the cube map texture
	 vec4 cubeMapColor = texture(cubemap, ReflectDir);
	 //vec4 cubeMapColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	if(DrawSkyBox) {
		FragColor = cubeMapColor;
	} else {
		//FragColor = mix(MaterialColor, CubeMapColor, ReflectFactor);
		FragColor = color * texture(image, uv);
	}
}
