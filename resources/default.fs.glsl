#version 430

in vec3 f_color;

out vec4 Color;

void main()
{
	Color = vec4(f_color, 1.0);
}