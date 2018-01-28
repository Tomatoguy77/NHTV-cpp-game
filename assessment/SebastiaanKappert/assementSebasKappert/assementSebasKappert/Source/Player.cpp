#include "Player.h"
#include <cmath>

using namespace std;
using namespace sf;

constexpr float paddleWidth{ 20.f }, paddleHeight{ 100.f }, paddleVelocity{ 10.f };
bool Playerleft;

RectangleShape shape;
Vector2f velocity;
float playerX, playerY, leftSide, rightSide, topSide, bottomSide;

Event event;
Clock reflectClock;
Time reflectTime;

//the player contructer
Player::Player(float mX, float mY)
{
	canReflect = false;
	//spawn the player on the right side of the pillar
	Playerleft = false;
	shape.setPosition(mX, mY);
	shape.setSize({ paddleWidth, paddleHeight });
	shape.setFillColor(Color::White);
	shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);

	playerX = shape.getPosition().x;
	playerY = shape.getPosition().y;
	leftSide = (playerX - shape.getSize().x / 2.f);

}

void Player::Draw(RenderWindow& window) {
	window.draw(shape);
	
}

void changeSide() {
	if (Playerleft = true)
	{
		return;
	}
	else if (Playerleft = false) {
		shape.setPosition(shape.getPosition().x + 200.f, shape.getPosition().y);

		return;

	}
	
}
//checks with the clock to see if if the player can reflect
void Player::Reflect() {

		if (reflectTime.asSeconds() <= 1) {
			return;
	} 
	
	reflectClock.restart();
	canReflect = true;
	shape.setFillColor(Color::Red);


}

void Player::StopReflect() {
	canReflect = false;
	shape.setFillColor(Color::White);
}

void Player::Update()
{
	//check the clock time
	reflectTime = reflectClock.getElapsedTime();

	if (reflectTime.asSeconds() > 1)
		StopReflect();

	//handle the player inputs
	if (Keyboard::isKeyPressed(Keyboard::Key::Space))
	{
		
		Reflect();
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && Playerleft != true)
	{
		Playerleft = true;
		shape.setPosition(shape.getPosition().x - 200.f, shape.getPosition().y);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && Playerleft == true) {
		Playerleft = false; 
		shape.setPosition(shape.getPosition().x + 200.f, shape.getPosition().y);
	}
	

	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && GetPlayerBounds().top > 0)
		velocity.y = -paddleVelocity;
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down) &&
		(GetPlayerBounds().top + GetPlayerBounds().height) < 600)
		velocity.y = paddleVelocity;
	else
		velocity.y = 0;
	shape.move(velocity);

}
//returns a floatrect of this shape
FloatRect Player::GetPlayerBounds() {
	RectangleShape* playerBounds = &shape;
	return playerBounds->getGlobalBounds();
}




Player::~Player()
{
}
