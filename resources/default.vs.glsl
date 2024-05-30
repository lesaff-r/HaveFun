#version 430

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;

uniform vec3 light_color;

uniform mat4 mvp;

out vec3 f_color;
out gl_PerVertex
{
	vec4 gl_Position;
};

void main()
{
	gl_Position = mvp * vec4(v_position, 1.0);
    f_color = light_color + v_color;
}