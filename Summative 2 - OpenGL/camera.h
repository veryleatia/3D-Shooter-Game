#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

class cCamera
{
public:

	void setEye(float _x, float _y, float _z)
	{
		eye = glm::vec3(_x, _y, _z);
	}

	void setCenter(float _x, float _y, float _z)
	{
		center = glm::vec3(_x, _y, _z);

	}

	void setUp(float _x, float _y, float _z)
	{
		up = glm::vec3(_x, _y, _z);

	}

	void setProjectionMatrix(float _fov, int _width, int _height, float _zNear, float _zFar)
	{
		projectionMatrix = glm::perspective(_fov, (GLfloat)_width / (GLfloat)_height, _zNear, _zFar);

	}
	void setViewMatrix(glm::vec3 _Eye, glm::vec3 _Center, glm::vec3 _Up)
	{
		viewMatrix = glm::lookAt(_Eye, _Center, _Up);

	}

	void setEyeX(float _x)
	{
		eye.x = _x;
	}

	void setCenterX(float _x)
	{
		center.x = _x;
	}

	void setEyeY(float _y)
	{
		eye.y = _y;
	}

	void setCenterY(float _y)
	{
		center.y = _y;
	}

	glm::vec3 getEye() 
	{
		return (eye);
	}

	glm::vec3 getCenter() 
	{
		return (center);
	}

	glm::vec3 getUp() 
	{
		return (up);
	}

	glm::mat4 getProjectionMatrix() 
	{
		return (projectionMatrix);
	}

	glm::mat4 getViewMatrix()
	{
		return (viewMatrix);
	}

	float getEyeX() 
	{
		return (eye.x);
	}

	float getCenterX() 
	{
		return (center.x);
	}

	float getEyeY() 
	{
		return (eye.y);
	}

	float getCenterY() 
	{
		return (center.y);
	}

	void update() 
	{
		viewMatrix = glm::lookAt(eye, center, up);
	}

private:
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
};