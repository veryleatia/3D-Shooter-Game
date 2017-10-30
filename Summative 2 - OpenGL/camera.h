#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"


class CCamera
{
	glm::mat4 ProjMatrix;
	glm::mat4 ViewMatrix;

	GLfloat x;
	GLfloat y;

	float cameraTime = 0.0f;

public:

	GLfloat currentX;

	void CCamera::CreateCamera(GLfloat _WindowWidth, GLfloat _WindowHeight)
	{
		
		ProjMatrix = glm::perspective(1.0f, (float)_WindowWidth / (float)_WindowHeight, 0.1f, 100.0f);
	}

	void CCamera::CreateCamera(GLfloat _WindowWidth, GLfloat _WindowHeight, GLfloat _posX, GLfloat _posY, GLuint _program)
	{

		ProjMatrix = glm::ortho((_posX - 800.0f / 2.0f) + 300, (_posX + 800.0f / 2.0f) + 300, 0.0f, _WindowHeight, 0.0f, 100.0f);
		x = (_posX - 800.0f / 2.0f) + 300;
		currentX = x;
	}

	void CCamera::UpdateCamera(GLfloat _WindowWidth, GLfloat _WindowHeight, GLfloat _posX, GLfloat _posY)
	{
		//moves camera with keyboard controls??
	}

	glm::mat4 CCamera::GetViewMatrix()
	{
		return ViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::mat4 CCamera::GetProjMatrix()
	{
		return ProjMatrix;
	}

};