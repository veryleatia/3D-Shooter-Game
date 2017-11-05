#pragma once

#include "sprite.h"

class cPlayer
{
public:
	cPlayer()
	{
		player = new cSprite();
		setSpeed(0.0f);
		player->setNewPosition(glm::vec3(-0.5f, -0.5f, 0.25f));
		player->setScale(glm::vec3(0.7f, 0.7f, 0.7f));
		player->setImage("assets/sprites/Player.png");
	}

	void init() 
	{
		player->init3d();

	}

	void render(glm::mat4 view, glm::mat4 projection)
	{
		player->render(view, projection);
	}

	GLfloat getSpeed() 
	{
		return (speed);
	}

	void setSpeed(GLfloat _speed) 
	{
		speed = _speed;
	}

	cSprite* getPlayer() 
	{
		return (player);
	}

private:
	float xPos;
	float yPos;
	cSprite* player;
	GLfloat speed;
};