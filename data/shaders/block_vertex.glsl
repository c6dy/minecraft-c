#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 v;
uniform mat4 p;

out vec2 texcoords;

void main()
{	
	texcoords = uv;
    gl_Position = p*v * vec4(position, 1.0f);
}