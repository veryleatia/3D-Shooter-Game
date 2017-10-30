#include "shape.h"
#include "utils.h"

//float Time = 0;

void CShape::init(GLuint _program, char* _filename, CCamera* _camera, float _width, float _height, Shape _shape, float _depth)
{
	glm::mat4 world;

	_meh = _shape;
	m_pos = glm::vec3(0.5f, -0.5f, 0.0f);

	world = glm::translate(glm::mat4(), m_pos);

	m_scale = glm::vec3(0.5f, 0.5f, 0.5f);
	m_rotate = glm::vec3(0.0, 1.0, 0.0);

	camera = _camera;

	fWidth = _width;
	fHeight = _height;


	if (_shape == Square)
	{
		_Quad[0].VertexPos.x = 0.0f;
		_Quad[0].VertexPos.y = 0.0f;
		_Quad[0].VertexColor.r = 0.0f;
		_Quad[0].VertexColor.g = 0.0f;
		_Quad[0].VertexColor.b = 0.0f;
		_Quad[0].VertexColor.a = 0.0f;
		_Quad[0].VertexTexCoord.x = 0.0f;
		_Quad[0].VertexTexCoord.y = 1.0f;

		_Quad[1].VertexPos.x = 0.0f;
		_Quad[1].VertexPos.y = 0.0f + _height;
		_Quad[1].VertexColor.r = 0.0f;
		_Quad[1].VertexColor.g = 0.0f;
		_Quad[1].VertexColor.b = 0.0f;
		_Quad[1].VertexColor.a = 0.0f;
		_Quad[1].VertexTexCoord.x = 0.0f;
		_Quad[1].VertexTexCoord.y = 0.0f;

		_Quad[2].VertexPos.x = 0.0f + _width;
		_Quad[2].VertexPos.y = 0.0f + _height;
		_Quad[2].VertexColor.r = 0.0f;
		_Quad[2].VertexColor.g = 0.0f;
		_Quad[2].VertexColor.b = 0.0f;
		_Quad[2].VertexColor.a = 0.0f;
		_Quad[2].VertexTexCoord.x = 1.0f;
		_Quad[2].VertexTexCoord.y = 0.0f;

		_Quad[3].VertexPos.x = 0.0f + _width;
		_Quad[3].VertexPos.y = 0.0f;
		_Quad[3].VertexColor.r = 0.0f;
		_Quad[3].VertexColor.g = 0.0f;
		_Quad[3].VertexColor.b = 0.0f;
		_Quad[3].VertexColor.a = 0.0f;
		_Quad[3].VertexTexCoord.x = 1.0f;
		_Quad[3].VertexTexCoord.y = 1.0f;

		GLuint indices[] =
		{
			0,1,2,
			0,2,3
		};


		program = _program;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_Quad), _Quad, GL_STATIC_DRAW);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(
			0, //Layout Location on vertix shader
			2, //3 vertices
			GL_FLOAT, // type of data
			GL_FALSE, // data normalized?
			sizeof(VertexFormat), // stride
			(GLvoid*)offsetof(VertexFormat, VertexPos)); // offset

		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(VertexFormat),
			(void*)offsetof(VertexFormat, VertexColor)
		);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, VertexTexCoord));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		int width, height;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		unsigned char* image = SOIL_load_image(_filename, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	else if (_shape == Cube)
	{
		_Cube[0].VertexPos.x = 0.0;
		_Cube[0].VertexPos.y = 0.0;
		_Cube[0].VertexPos.z = 0.0;
		_Cube[0].VertexColor.r = 0.0f;
		_Cube[0].VertexColor.g = 0.0f;
		_Cube[0].VertexColor.b = 0.0f;
		_Cube[0].VertexColor.a = 0.0f;
		_Cube[0].VertexTexCoord.x = 0.0f;
		_Cube[0].VertexTexCoord.y = 1.0f;

		_Cube[1].VertexPos.x = 0.0+_width;
		_Cube[1].VertexPos.y = 0.0;
		_Cube[1].VertexPos.z = 0.0;
		_Cube[1].VertexColor.r = 0.0f;
		_Cube[1].VertexColor.g = 0.0f;
		_Cube[1].VertexColor.b = 0.0f;
		_Cube[1].VertexColor.a = 0.0f;
		_Cube[1].VertexTexCoord.x = 0.0f;
		_Cube[1].VertexTexCoord.y = 0.0f;

		_Cube[2].VertexPos.x = 0.0+_width;
		_Cube[2].VertexPos.y = 0.0+_height;
		_Cube[2].VertexPos.z = 0.0;
		_Cube[2].VertexColor.r = 0.0f;
		_Cube[2].VertexColor.g = 0.0f;
		_Cube[2].VertexColor.b = 0.0f;
		_Cube[2].VertexColor.a = 0.0f;
		_Cube[2].VertexTexCoord.x = 1.0f;
		_Cube[2].VertexTexCoord.y = 0.0f;

		_Cube[3].VertexPos.x = 0.0;
		_Cube[3].VertexPos.y = 0.0+ _height;
		_Cube[3].VertexPos.z = 0.0;
		_Cube[3].VertexColor.r = 0.0f;
		_Cube[3].VertexColor.g = 0.0f;
		_Cube[3].VertexColor.b = 0.0f;
		_Cube[3].VertexColor.a = 0.0f;
		_Cube[3].VertexTexCoord.x = 1.0f;
		_Cube[3].VertexTexCoord.y = 1.0f;

		_Cube[4].VertexPos.x = 0.0;
		_Cube[4].VertexPos.y = 0.0;
		_Cube[4].VertexPos.z = 0.0+_depth;
		_Cube[4].VertexColor.r = 0.0f;
		_Cube[4].VertexColor.g = 0.0f;
		_Cube[4].VertexColor.b = 0.0f;
		_Cube[4].VertexColor.a = 0.0f;
		_Cube[4].VertexTexCoord.x = 1.0f;
		_Cube[4].VertexTexCoord.y = 0.0f;

		_Cube[5].VertexPos.x = 0.0 + _width;
		_Cube[5].VertexPos.y = 0.0;
		_Cube[5].VertexPos.z =0.0 +_depth;
		_Cube[5].VertexColor.r = 0.0f;
		_Cube[5].VertexColor.g = 0.0f;
		_Cube[5].VertexColor.b = 0.0f;
		_Cube[5].VertexColor.a = 0.0f;
		_Cube[5].VertexTexCoord.x = 0.0f;
		_Cube[5].VertexTexCoord.y = 0.0f;

		_Cube[6].VertexPos.x = 0.0+_width;
		_Cube[6].VertexPos.y = 0.0+_height;
		_Cube[6].VertexPos.z = 0.0+_depth;
		_Cube[6].VertexColor.r = 0.0f;
		_Cube[6].VertexColor.g = 0.0f;
		_Cube[6].VertexColor.b = 0.0f;
		_Cube[6].VertexColor.a = 0.0f;
		_Cube[6].VertexTexCoord.x = 0.0f;
		_Cube[6].VertexTexCoord.y = 1.0f;

		_Cube[7].VertexPos.x = 0.0;
		_Cube[7].VertexPos.y = 0.0+_height;
		_Cube[7].VertexPos.z = 0.0+_depth;
		_Cube[7].VertexColor.r = 0.0f;
		_Cube[7].VertexColor.g = 0.0f;
		_Cube[7].VertexColor.b = 0.0f;
		_Cube[7].VertexColor.a = 0.0f;
		_Cube[7].VertexTexCoord.x = 1.0f;
		_Cube[7].VertexTexCoord.y = 1.0f;

		
		//etc... up to _Cube[8]

		//create cube here

		//create indices for cube here also
		GLuint indi[] =
		{
			0, 1, 2,
			0, 2, 3,
			1,2,6,
			6,5,1,
			4,5,6,
			6,7,4,
			2,3,6,
			6,3,7,
			0,7,3,
			0,4,7,
			0,1,5,
			0,5,4
		};

		program = _program;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_Cube), _Cube, GL_STATIC_DRAW);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indi), indi, GL_STATIC_DRAW);

		glVertexAttribPointer(
			0, //Layout Location on vertix shader
			3, //3 vertices
			GL_FLOAT, // type of data
			GL_FALSE, // data normalized?
			sizeof(Vertex3D), // stride
			(GLvoid*)offsetof(Vertex3D, VertexPos)); // offset

		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex3D),
			(void*)offsetof(Vertex3D, VertexColor)
		);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, VertexTexCoord));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		int width, height;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		unsigned char* image = SOIL_load_image(_filename, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		

	}
	else if (_shape == Pyramid)
	{
		//create pyrmaid here
		//no idea how to do that
		_Pyramid[0].VertexPos.x = _width;
		_Pyramid[0].VertexPos.y = 0.0f;
		_Pyramid[0].VertexPos.z = _depth;
		_Pyramid[0].VertexColor.r = 0.0f;
		_Pyramid[0].VertexColor.g = 0.0f;
		_Pyramid[0].VertexColor.b = 0.0f;
		_Pyramid[0].VertexColor.a = 0.0f;
		_Pyramid[0].VertexTexCoord.x = 0.0f;
		_Pyramid[0].VertexTexCoord.y = 1.0f;

		_Pyramid[1].VertexPos.x = _width;
		_Pyramid[1].VertexPos.y = 0.0f;
		_Pyramid[1].VertexPos.z = -_depth;
		_Pyramid[1].VertexColor.r = 0.0f;
		_Pyramid[1].VertexColor.g = 0.0f;
		_Pyramid[1].VertexColor.b = 0.0f;
		_Pyramid[1].VertexColor.a = 0.0f;
		_Pyramid[1].VertexTexCoord.x = 0.0f;
		_Pyramid[1].VertexTexCoord.y = 0.0f;

		_Pyramid[2].VertexPos.x = -_width;
		_Pyramid[2].VertexPos.y = 0.0f;
		_Pyramid[2].VertexPos.z = -_depth;
		_Pyramid[2].VertexColor.r = 0.0f;
		_Pyramid[2].VertexColor.g = 0.0f;
		_Pyramid[2].VertexColor.b = 1.0f;
		_Pyramid[2].VertexColor.a = 0.0f;
		_Pyramid[2].VertexTexCoord.x = 1.0f;
		_Pyramid[2].VertexTexCoord.y = 0.0f;

		_Pyramid[3].VertexPos.x = -_width;
		_Pyramid[3].VertexPos.y = 0.0f;
		_Pyramid[3].VertexPos.z = _depth;
		_Pyramid[3].VertexColor.r = 0.0f;
		_Pyramid[3].VertexColor.g = 1.0f;
		_Pyramid[3].VertexColor.b = 0.0f;
		_Pyramid[3].VertexColor.a = 0.0f;
		_Pyramid[3].VertexTexCoord.x = 1.0f;
		_Pyramid[3].VertexTexCoord.y = 1.0f;

		_Pyramid[4].VertexPos.x = 0.0f;
		_Pyramid[4].VertexPos.y = _height;
		_Pyramid[4].VertexPos.z = 0.0f;
		_Pyramid[4].VertexColor.r = 1.0f;
		_Pyramid[4].VertexColor.g = 1.0f;
		_Pyramid[4].VertexColor.b = 1.0f;
		_Pyramid[4].VertexColor.a = 0.0f;
		_Pyramid[4].VertexTexCoord.x = 0.5f;
		_Pyramid[4].VertexTexCoord.y = 1.0f;

		GLuint ind[] =
		{
			0,1,2,
			0,2,3,
			0,4,3,
			1,4,0,
			2,4,1,
			3,4,2,
		};

		program = _program;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_Pyramid), _Pyramid, GL_STATIC_DRAW);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

		glVertexAttribPointer(
			0, //Layout Location on vertix shader
			3, //3 vertices
			GL_FLOAT, // type of data
			GL_FALSE, // data normalized?
			sizeof(Vertex3D), // stride
			(GLvoid*)offsetof(Vertex3D, VertexPos)); // offset

		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex3D),
			(void*)offsetof(Vertex3D, VertexColor)
		);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, VertexTexCoord));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		int width, height;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		unsigned char* image = SOIL_load_image(_filename, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		
	}
	else if (_shape == Globe)
	{
		//create globe here
		
	}

	

};

void CShape::update() {

	if (_meh == Square)
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_Quad), _Quad, GL_STATIC_DRAW);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else if (_meh == Pyramid)
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_Pyramid), _Pyramid, GL_STATIC_DRAW);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else if (_meh == Cube)
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_Cube), _Cube, GL_STATIC_DRAW);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	



};

void CShape::render(float _time) {

	glUseProgram(program);

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime");
	int currentTime = glutGet(GLUT_ELAPSED_TIME);

	glm::mat4 trans = glm::translate(glm::mat4(), m_pos);
	glm::mat4 rotate = glm::rotate(trans, (glm::radians(1.0f) *currentTime / 10), m_rotate);

	glm::mat4 scale = glm::scale(rotate, m_scale);


	//glm::mat4 model = glm::rotate(glm::mat4(), glm::radians(90.0f) *currentTime / 100, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 model = scale;

	GLint modelLocation = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLint projLocation = glGetUniformLocation(program, "proj");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(camera->GetProjMatrix()));

	GLint viewLocation = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));


	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);

	// bind vao

	if (_meh == Square)
	{
		glm::mat4 trans = glm::translate(glm::mat4(), m_pos);
		glm::mat4 rotate;// = glm::rotate(glm::mat4(), (2.0f *currentTime / 10000), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 scale = glm::scale(glm::mat4(), m_scale);


		glm::mat4 model = rotate * trans * scale;

		GLint modelLocation = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		GLint projLocation = glGetUniformLocation(program, "proj");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(camera->GetProjMatrix()));

		GLint viewLocation = glGetUniformLocation(program, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));


		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // unbind vao
	}
	else if (_meh == Pyramid)
	{
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // unbind vao
	}
	else if (_meh == Cube)
	{
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	
}

void CShape::TranslateRelative(glm::vec3 pos)
{
	m_pos += pos;
}

void CShape::TranslateAbsolute(glm::vec3 pos)
{
	m_pos = pos;
}