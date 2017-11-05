#pragma once

#include "sprite.h"

class cPowerup
{
public:
	cPowerup()
	{
		xPos = rand() % 6 - 3;
		yPos = rand() % 6 - 3;
		Powerup = new cSprite();
		setSpeed(0);
		Powerup->setNewPosition(glm::vec3(xPos, yPos, 0.25f));
		Powerup->setScale(glm::vec3(0.7f, 0.7f, 0.7f));
		Powerup->setImage("assets/sprites/Pickup.png");
	}


	void init()
	{
		Powerup->init3d();
	}

	void render(glm::mat4 view, glm::mat4 projection)
	{
		Powerup->render(view, projection);
	}

	void update(float _deltaTime, float playerxPos, float playeryPos)
	{
		Powerup->setNewPositionX(xPos);
		Powerup->setNewPositionY(yPos);
	}

	GLfloat getSpeed()
	{
		return (speed);
	}

	void setSpeed(GLfloat _speed)
	{
		speed = _speed;
	}

	cSprite* getPowerup()
	{
		return (Powerup);
	}

private:
	float xPos;
	float yPos;
	float xSpeed;
	float ySpeed;
	cSprite* Powerup;
	GLfloat speed;
};