#pragma once

#include "sprite.h"

class cEnemies
{
public:
	cEnemies(float fSpeed) 
	{
		xPos = rand() % 10 - 5;
		yPos = rand() % 10 - 5;
		Enemy = new cSprite();
		setSpeed(fSpeed);
		Enemy->setNewPosition(glm::vec3(xPos, yPos, 0.25f));
		Enemy->setScale(glm::vec3(0.7f, 0.7f, 0.7f));
		Enemy->setImage("assets/sprites/Enemy.png");
	}

	void init() 
	{
		Enemy->init3d();
	}

	void render(glm::mat4 view, glm::mat4 projection) 
	{
		Enemy->render(view, projection);

	}

	void update(float _deltaTime, float playerxPos, float playeryPos) 
	{
		
		if (Enemy->getNewPositionX() > playerxPos)
		{
			xPos -= speed * _deltaTime;
		}
		if (Enemy->getNewPositionX() < playerxPos)
		{
			xPos += speed * _deltaTime;
		}
		if (Enemy->getNewPositionY() > playeryPos)
		{
			yPos -= speed * _deltaTime;
		}
		if (Enemy->getNewPositionY() < playeryPos)
		{
			yPos += speed * _deltaTime;
		}

		Enemy->setNewPositionX(xPos);
		Enemy->setNewPositionY(yPos);
	}

	GLfloat getSpeed() 
	{
		return (speed);

	}

	void setSpeed(GLfloat _speed)
	{
		speed = _speed;

	}

	cSprite* getEnemy() 
	{
		return (Enemy);
	}

private:
	float xPos;
	float yPos;
	float xSpeed;
	float ySpeed;
	cSprite* Enemy;
	GLfloat speed;
};