#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Block {
public:
	RectangleShape* blockshape;

	float blockWidht, blockHeight;
	int x, y;
	void IsHit();
	FloatRect GetBlockBounds();
	~Block();
	Block::Block(float mX, float mY, int mHealth, bool isPlayerBlock);
	void SetHealth(int newHealth);
	void Update();
	void Draw(RenderWindow & window);
	void ChangeColor();
	bool isActive;
private:
	int health;
	float PlayerBlock;
};