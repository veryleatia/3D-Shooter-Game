#version 430 core



in vec3 outColor;
in vec2 TexCoord;
out vec4 color;


in vec3 outPosition;

uniform float currentTime;
uniform sampler2D Texture;


void main()
{
	//color = texture(Texture, TexCoord);//*vec4(outColor, 1.0f)* abs(sin(currentTime));
	color = texture(Texture, TexCoord);
	//color = vec4(0.5f, 0.5f, 0.2f, 1.0f);
}