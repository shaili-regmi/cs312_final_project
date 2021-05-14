#version 400

layout (location = 0) in vec3 vPos;
//layout (location = 1) in vec3 vNorm;

out vec3 ReflectDir; // The direction of the reflected ray

uniform bool DrawSkyBox; // Are we drawing the sky box?
uniform vec3 uCameraPos;
uniform float uSize;
uniform vec3 uOffset;
uniform vec4 uColor;

//uniform mat4 vM;
uniform mat4 uVP;

out vec4 color;
out vec2 uv;

void main()
{

	vec3 new_pos = vPos - vec3(0.5f, 0.5f, 0.0f);

	if(DrawSkyBox) {
	
		ReflectDir = new_pos;
		gl_Position = uVP * vec4(vPos, 1.0);

    } else {

		color = uColor;
		uv = vPos.xy;

		mat4 trans_matrix = mat4 (1.0f, 0.0f, 0.0f, 0.0f, 
									0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f, 
									uOffset.x, uOffset.y, uOffset.z, 1.0f);
 
		mat4 scale_matrix = mat4 (uSize, 0.0f, 0.0f, 0.0f,
									0.0f, uSize, 0.0f, 0.0f,
									0.0f, 0.0f, uSize, 0.0f,
									0.0f, 0.0f, 0.0f, 1.0f);

		vec3 cam_z = normalize(uCameraPos - uOffset);
		vec3 cam_x = cross(vec3(0,1,0), normalize(cam_z));
		vec3 cam_y = cross(normalize(cam_z), normalize(cam_x));

		mat4 rotation_matrix = mat4 (vec4(cam_x, 0), vec4(cam_y, 0), vec4(cam_z, 0), vec4(0,0,0,1));

		mat4 transformation = trans_matrix * rotation_matrix * scale_matrix;

		gl_Position = uVP * transformation * vec4(new_pos, 1.0);
    }

 }
