
#include "Block.h"
using namespace std;
using namespace sf;




bool destroyed;
//float x, y, leftSide, rightSide, topSide, bottomside;
Block::Block(float mX, float mY, int mHealth, bool isPlayerBlock)
{
	//check if this block is to be defended by the player
	PlayerBlock = isPlayerBlock;
	isActive = true;
	//decide the size of the block
	if (PlayerBlock)
		blockHeight = 550.f;
	else
		blockHeight = 60.f;
	blockWidht = 60.f;
	
	destroyed = false;
	blockshape = new RectangleShape();
	blockshape->setPosition(mX, mY);
	blockshape->setSize({ blockWidht,blockHeight });
	//blockshape->cg(mColor);
	blockshape->setOrigin(blockWidht / 2.f, blockHeight / 2.f);
	health = mHealth;
	ChangeColor();

	//x = blockshape->getPosition().x;
	//y = blockshape->getPosition().y;
}

void Block::SetHealth(int newHealth) {
	health = newHealth;
	ChangeColor();
}
void Block::Update()
{
	
	if (health == 0)
	{
		isActive = false;

	}
}
void Block::Draw(RenderWindow& window) {
	if (isActive)
		window.draw(*blockshape);


}

void Block::ChangeColor() {
	switch (health)
	{
	case 1: blockshape->setFillColor(Color::Red);
		break;
	case 2: blockshape->setFillColor(Color::Yellow);
		break;
	case 3: blockshape->setFillColor(Color::Magenta);
		break;
	case 4: blockshape->setFillColor(Color::Green);
		break;
	case 5: blockshape->setFillColor(Color::Blue);
		break;
	case 6: blockshape->setFillColor(Color::Cyan);

	default: 
		break;
	}
}
//function to be called when the player is hit
void Block::IsHit() {
	
	health--;
	ChangeColor();
}
//returns a floatrect of the shape
FloatRect Block::GetBlockBounds() {
	return blockshape->getGlobalBounds();

}
Block::~Block()
{

	
}