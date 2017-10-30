#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <string>
#include "utils.h"
#include "camera.h"
#include "Dependencies\soil\SOIL.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"


class CShape
{

public:

	VertexFormat _Quad[4];
	Vertex3D _Cube[8];
	Vertex3D _Pyramid[5];
	//specify globe
	//specify pyramid

	GLuint program, vao, vbo, ebo, texture;
	CCamera* camera;

	float deltatime;

	float fWidth;
	float fHeight;
	float Time;

	Shape _meh;

	glm::vec3 m_pos;
	glm::vec3 m_scale;
	glm::vec3 m_rotate;

	CShape::~CShape() {};

	void CShape::init(GLuint _program, char* _filename, CCamera* _camera, float _width, float _height, Shape _shape, float _depth);
	void CShape::update();
	void CShape::render(float _time);
	void CShape::TranslateRelative(glm::vec3 pos);
	void CShape::TranslateAbsolute(glm::vec3 pos);




};