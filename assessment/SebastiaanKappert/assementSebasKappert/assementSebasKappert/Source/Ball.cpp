#include "Ball.h"
#include "Player.h"

using namespace sf;
CircleShape shape;
constexpr float ballRadius{ 10.f }, ballVelocity{ 8.f };

Ball::Ball(float mX,float mY)
{
	ballVector = new Vector2f{-ballVelocity, ballVelocity};
	ballShape = new CircleShape();
	ballShape->setPosition(mX, mY);
	ballShape->setRadius(ballRadius);
	ballShape->setFillColor(Color::Red);
	ballShape->setOrigin(ballRadius, ballRadius);
	isActive = true;
	//
	
	
}


void Ball::Draw(RenderWindow& window) {
	if(isActive)
		window.draw(*ballShape);

}



void Ball::Update() {
	//make sure the ball doesn't leave the screen by reversing its velocity
	if (GetBallBounds().left <= 0)
	{
		ballVector->x = ballVelocity;
	}
		
	else if (GetBallBounds().left + GetBallBounds().width >= 1600) {
		ballVector->x = -ballVelocity;

	 }


	if (GetBallBounds().top  <= 0)
	{
		ballVector->y = ballVelocity;
		
	}
	else if (GetBallBounds().top + GetBallBounds().height >= 600) {
		ballVector->y = -ballVelocity;

	}
	//move the ball
	ballShape->move(*ballVector);
		
}


//returns a floatrect of the shape
FloatRect Ball::GetBallBounds() {
	return ballShape->getGlobalBounds();
}

void Ball::BallColisionPlayer(Player & player)
{
	//first check if the player can currently reflect
	if (player.canReflect) {

		if (player.GetPlayerBounds().intersects(GetBallBounds())) {
			if (ballVector->x >= 0)
				ballVector->x = -ballVector->x;
			else if (ballVector->x < 0)
				ballVector->x = -ballVector->x;

			if (GetBallBounds().top <= (player.GetPlayerBounds().top + (player.GetPlayerBounds().height / 2)))
			{
				ballVector->y = 8.f;
			}
			else if (GetBallBounds().top > (player.GetPlayerBounds().top + (player.GetPlayerBounds().height / 2))) {
				ballVector->y = -8.f;

			}

		}

	}

}
void Ball::BallColisionBlock(Block* block) {

	if (block->GetBlockBounds().intersects(GetBallBounds())) {
		//use the blocks function for when it gets hit
		block->IsHit();
		//decide which way to send the ball by calculating 
		if (ballVector->x >= 0)
		{
			ballVector->x = -ballVector->x;
			if ((GetBallBounds().top - block->GetBlockBounds().top) <= GetBallBounds().height)
			{
				ballVector->y = -ballVector->y;
			}
			if (((GetBallBounds().top + GetBallBounds().height) - block->GetBlockBounds().top + block->GetBlockBounds().height) <= GetBallBounds().height)
			{
				ballVector->y = -ballVector->y;
			}
		}
			
		else if (ballVector->x < 0) {
			ballVector->x = -ballVector->x;
			if ((GetBallBounds().top - block->GetBlockBounds().top) <= GetBallBounds().height)
			{
				ballVector->y = -ballVector->y;
			
			}
			if (((GetBallBounds().top + GetBallBounds().height) - block->GetBlockBounds().top + block->GetBlockBounds().height) <= GetBallBounds().height)
			{
				ballVector->y = -ballVector->y;
			}
		}
	}
		
	
	
	
}

Ball::~Ball()
{
}
