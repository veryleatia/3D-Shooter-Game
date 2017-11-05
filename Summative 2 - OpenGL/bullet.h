#pragma once

#include "sprite.h"

class cBullet
{
public:
	cBullet(float fxSpeed, float fySpeed, float fxPos, float fyPos)
	{
		bullet = new cSprite();
		setSpeed(0.05f);
		// Players position
		bullet->setNewPosition(glm::vec3(fxPos, fyPos, 0.25f));

		bullet->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
		bullet->setImage("assets/sprites/bullet.png");

		xSpeed = fxSpeed;
		ySpeed = fySpeed;
		xPos = fxPos;
		yPos = fyPos;
	}

	void init()
	{
		bullet->init3d();
	}

	void render(glm::mat4 view, glm::mat4 projection)
	{
		bullet->render(view, projection);
	}

	void update(float DeltaTime) 
	{
		xPos += xSpeed * (speed * DeltaTime);
		yPos += ySpeed * (speed * DeltaTime);

		bullet->setNewPositionX(xPos);
		bullet->setNewPositionY(yPos);
	}

	GLfloat getSpeed() 
	{
		return (speed);

	}

	void setSpeed(GLfloat _speed) 
	{
		speed = _speed;

	}

	cSprite* getBullet() 
	{
		return (bullet);
	}

private:
	cSprite* bullet;
	GLfloat speed;
	float xPos;
	float yPos;
	float xSpeed;
	float ySpeed;
};