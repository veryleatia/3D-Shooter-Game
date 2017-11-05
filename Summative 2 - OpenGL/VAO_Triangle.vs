#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 outColor; 
out vec2 TexCoord;
out vec3 outPosition;

uniform float currentTime;
uniform int iSpriteFrame = 0;

uniform int pauto;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
//rotation

void main(void)
{

	gl_Position = proj * view * model * vec4(position,  1.0);
	//gl_Position= transform * vec4(position, 1.0);
	//gl_Position = vec4(position.x, position.y, position.z, 1.0);
        outColor = color;
		
	TexCoord = texCoord;
//	if (pauto > 1000)
//	{
//    TexCoord.x = texCoord.x+0.125;
//	}
//	TexCoord.y = texCoord.y; 	
	
	//gl_Position.x = position.x * cos(currentTime)- position.y*(sin(currentTime));
	//gl_Position.y = position.x * (sin(currentTime)) + position.y * cos(currentTime);

	
		outPosition = position;
}