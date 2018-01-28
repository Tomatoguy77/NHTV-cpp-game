#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "Block.h"
#include <SFML/Audio.hpp>

using namespace sf;

class Ball
{
public:
	CircleShape* ballShape;
	Vector2f* ballVector;
	Ball(float mX, float mY);
	void Update();
	void Move();
	~Ball();
	bool isActive;
	

public:
	void Draw(RenderWindow & window);
	void BallColisionPlayer(Player& player);
	FloatRect Ball::GetBallBounds();
	void BallColisionBlock(Block * block);
	

};

