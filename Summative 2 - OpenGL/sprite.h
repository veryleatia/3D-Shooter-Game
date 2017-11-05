#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "ShaderLoader.h"

class cSprite
{
public:
	cSprite();
	~cSprite();

	void setImage(char *_image);
	void setNewPosition(glm::vec3 _position);
	void setRadian(float _r);
	void rotateX(float _f);
	void rotateY(float _f);
	void rotateZ(float _f);


	float getRadian();

	void init();
	void init3d();
	void render(glm::mat4 view, glm::mat4 projection);

	float getNewPositionX();
	float getNewPositionY();

	void setNewPositionX(float _f);
	void setNewPositionY(float _f);

	void setScale(glm::vec3 scale);

private:
	GLuint program, vao, vbo, ebo, texture;
	glm::vec3 newPosition;
	char* characterImage;
	glm::mat4 scale;
	float radian;
	glm::mat4 model;
	glm::mat4 rotation;

};