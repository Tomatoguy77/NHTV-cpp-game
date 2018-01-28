#pragma once
#include <SFML\Graphics.hpp>


using namespace sf;
//using namespace std;

class Player
{
public:
	Player(float, float);
	~Player();
	void Update();


public:
	void Draw(RenderWindow& window);
	FloatRect GetPlayerBounds();
	//void Player::Reflect();
	bool canReflect;
 
private:
	void Player::Reflect();
	void StopReflect();
};

