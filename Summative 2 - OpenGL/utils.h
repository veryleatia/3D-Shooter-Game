#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

//Position struct
struct Pos
{
	GLfloat x;
	GLfloat y;
};

//position for 3d object
struct Pos3D
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

//Color struct
struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;

};

//Texture Coordinates struct
struct TexCoord
{
	float x;
	float y;
};

//Vertex Format
struct VertexFormat
{
	Pos VertexPos;
	Color VertexColor;
	TexCoord VertexTexCoord;
};

//vertex format for 3D shapes
struct Vertex3D
{
	Pos3D VertexPos;
	Color VertexColor;
	TexCoord VertexTexCoord;
};

//shape type??
enum Shape
{
	Square,
	Cube,
	Globe,
	Pyramid
};