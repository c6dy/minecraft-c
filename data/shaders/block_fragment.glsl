#version 330

in vec2 texcoords;

out vec4 color;

uniform sampler2D u_texture;
uniform vec3 camera_position;

void main()
{	
	vec4 frag_color = texture(u_texture, texcoords);
    color = frag_color;
}