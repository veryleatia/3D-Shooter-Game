#include "sprite.h"

cSprite::cSprite()
{

}

cSprite::~cSprite()
{

}

void cSprite::setImage(char *_image)
{
	characterImage = _image;
}

void cSprite::setNewPosition(glm::vec3 _position)
{
	newPosition = _position;
}

void cSprite::setRadian(float _f)
{
	radian = _f;
}

void cSprite::rotateX(float _f)
{
	rotation = glm::rotate(glm::mat4(), glm::radians(_f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void cSprite::rotateY(float _f)
{
	rotation = glm::rotate(glm::mat4(), glm::radians(_f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void cSprite::rotateZ(float _f)
{
	rotation = glm::rotate(glm::mat4(), glm::radians(_f), glm::vec3(0.0f, 0.0f, 1.0f));
}

float cSprite::getRadian()
{
	return (radian);
}

void cSprite::setNewPositionX(float _f)
{
	newPosition.x = _f;
}

void cSprite::setNewPositionY(float _f)
{
	newPosition.y = _f;
}

float cSprite::getNewPositionX()
{
	return newPosition.x;
}

float cSprite::getNewPositionY()
{
	return newPosition.y;
}

void cSprite::setScale(glm::vec3 _scale)
{
	scale = glm::scale(glm::mat4(), _scale);
}

void cSprite::init3d()
{
	int width;
	int height;

	setRadian(0.0f);

	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VAO_Triangle.vs", "VAO_Triangle.fs");

	GLfloat vertices[] = {
		// Position			  // Color
		//-0.25f, 0.125f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // Top Left
		//0.25f, 0.125f, 0.0f,    1.0f, 1.0f, 1.0f,  0.5f, 0.0f, // Top Right
		//0.25f, -0.125f, 0.0f,   1.0f, 1.0f, 1.0f,  0.5f, 1.0f, // Bottom Right
		//-0.25f, -0.125f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f  // Bottom Left
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		// Fill in the back face vertex data.
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		// Fill in the top face vertex data.
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		// Fill in the bottom face vertex data.
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		// Fill in the left face vertex data.
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		// Fill in the right face vertex data.
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	GLuint indices[] = {
		//0, 1, 2, // First Triangle
		//0, 2, 3  // Second Triangle

		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,
		// bottom
		12, 13, 14,
		12, 14, 15,
		// left
		16, 17, 18,
		16, 18, 19,
		// right
		20, 21, 22,
		20, 22, 23,
	};

	glGenBuffers(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glVertexAttribPointer(
		0, // Layout location on vertex shader
		3, // 3 vertices
		GL_FLOAT, // type of data
		GL_FALSE, // data normalized?
		8 * sizeof(GLfloat), // stride
		(GLvoid*)0); // offset

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat), // size of data
		(GLvoid*)(3 * sizeof(GLfloat))); // offset

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat))
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	unsigned char* image = SOIL_load_image(characterImage,
		&width,
		&height,
		0,
		SOIL_LOAD_RGBA);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image
	);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void cSprite::init()
{
	int width;
	int height;

	setRadian(0.0f);

	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VAO_Triangle.vs", "VAO_Triangle.fs");

	GLfloat vertices[] = {
		// Position			  // Color
		-0.25f, 0.125f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // Top Left
		0.25f, 0.125f, 0.0f,    1.0f, 1.0f, 1.0f,  0.5f, 0.0f, // Top Right
		0.25f, -0.125f, 0.0f,   1.0f, 1.0f, 1.0f,  0.5f, 1.0f, // Bottom Right
		-0.25f, -0.125f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f  // Bottom Left

	};

	GLuint indices[] = {
		0, 1, 2, // First Triangle
		0, 2, 3  // Second Triangle
	};

	glGenBuffers(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glVertexAttribPointer(
		0, // Layout location on vertex shader
		3, // 3 vertices
		GL_FLOAT, // type of data
		GL_FALSE, // data normalized?
		8 * sizeof(GLfloat), // stride
		(GLvoid*)0); // offset

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat), // size of data
		(GLvoid*)(3 * sizeof(GLfloat))); // offset

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat))
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	unsigned char* image = SOIL_load_image(characterImage,
		&width,
		&height,
		0,
		SOIL_LOAD_RGBA);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image
	);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void cSprite::render(glm::mat4 _view, glm::mat4 _projection)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(
		0, // Layout location on vertex shader
		3, // 3 vertices
		GL_FLOAT, // type of data
		GL_FALSE, // data normalized?
		8 * sizeof(GLfloat), // stride
		(GLvoid*)0); // offset

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat), // size of data
		(GLvoid*)(3 * sizeof(GLfloat))); // offset

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat))
	);

	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME); // get current time
	currentTime = currentTime / 1000; // convert millisecond to seconds

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLocation, currentTime);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glCullFace(GL_FRONT);

	glUseProgram(program);

	//translation
	model = glm::translate(glm::mat4(), newPosition);
	//glm::mat4 rotation = glm::rotate(glm::mat4(), radian, glm::vec3(0.0, 0.0, 1.0));
	//camera
	glm::mat4 view = _view;/*glm::lookAt(eye, center, up);*/
	glm::mat4 projection = _projection;/*glm::perspective(45.0f, (GLfloat)1000 / (GLfloat)1000, 0.1f, 100.0f);*/

	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint rotationLoc = glGetUniformLocation(program, "rotation");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");
	GLint scaleLoc = glGetUniformLocation(program, "scale");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, glm::value_ptr(rotation));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scale));


	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);


}