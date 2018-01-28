#include <SFML/Graphics.hpp>
#include <cmath>
#include "Ball.h"
#include "Block.h"
#include "Player.h"
using namespace std;
using namespace sf;

constexpr float blockWidth{ 60.f }, blockHeight{ 60.f };
int blocknumber = 0;
enum GameState{start, game} gamestates;

int main()
{

	//ONLY USE TEX IN RELEASE 
	//there is a problem with the debug libraries that hasn't been solved yet
	//load the start texture
	Texture tex;
	tex.loadFromFile("Art/Start2.png");
	Sprite tut;

	tut.setTexture(tex);	
	tut.setScale(1,1);
	gamestates = start;



	
	

	
	RenderWindow window{ { 1600, 600}, "Assessment Sebastiaan Kappert" };
	window.setFramerateLimit(60);

	vector<Block*> blocksRight;
	vector<Block*> blocksMiddle;
	vector<Block*> blocksLeft;

	//spawns the blocks on the right side
	for (int iX = 0; iX > -2; iX--) {
		for (int iY = 0; iY < 4; iY++) {
			Block* tempBlock = new Block((1600  - ((iX - 1) ))  - (iX * blockWidth) - 100, (iY + 3) * (blockHeight + 3), 1, false);
			blocksRight.push_back(tempBlock);
		//	cout << tempBlock->x << "x " << tempBlock->y << "y ";
		}
	}
		
	//spawns the blocks on the left side
	for (int iX = 0; iX > -2; iX--) {
		for (int iY = 0; iY < 4; iY++) {
			Block* tempBlock = new Block((0 + ((iX + 1))) + (iX * blockWidth) + 100, (iY + 3) * (blockHeight + 3), 1, false);
			blocksLeft.push_back(tempBlock);
		}
	}
	//spawns the players blocks in the middle
	for (int iX = 0; iX > -2; iX--) {
		for (int iY = 0; iY < 1; iY++) {
			Block* tempBlock = new Block((730 + ((iX + 1))) + (iX * blockWidth) + 100, (iY + 3) * (blockHeight + 6) + 100,6 , true);
			blocksMiddle.push_back(tempBlock);
		}
	}
	//spawn both of the balls on the screen
	Ball* Leftball = new Ball(500.f, 50.f);
	Ball* Rightball = new Ball(1500.f, 50.f);



	//spawns the player 
	Player player(900.f, 300.f);
	
	int inactiveBlocksMiddle = 0;
	int inactiveBlocksSide = 0;
	while (true)
	{
		//stops the game if escape is pressed
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

		switch (gamestates)
		{
		case start:
			window.clear(Color::Black);
			window.draw(tut);

			window.display();
			if (Keyboard::isKeyPressed(Keyboard::Key::Return)) {
				//reset all the blocks for when the player restarts the games
				for (int i = 0; i < blocksMiddle.size(); i++)
				{
					blocksMiddle[i]->SetHealth(6);
					blocksMiddle[i]->isActive = true;					
				}
				for (int i = 0; i < blocksLeft.size(); i++)
				{
					blocksRight[i]->isActive = true;
					blocksRight[i]->SetHealth(1);

					blocksLeft[i]->SetHealth(1);

					blocksLeft[i]->isActive = true;					
				}
				 inactiveBlocksMiddle = 0;
				 inactiveBlocksSide = 0;
				gamestates = game;
			}
				
			break;
		case game:
			
			window.clear(Color::Black);
			player.Update();
			//loop trough all the blocks and use their respective collison, update and draw function
			for (auto& Block : blocksLeft) {
				if (Block->isActive)
				{
					Leftball->BallColisionBlock(Block);
					Rightball->BallColisionBlock(Block);
				}
				Block->Draw(window);
				Block->Update();
			}

			for (auto& Block : blocksRight) {
				if (Block->isActive)
				{
					Leftball->BallColisionBlock(Block);
					Rightball->BallColisionBlock(Block);

				}

				Block->Draw(window);
				Block->Update();

			}
			for (auto& Block : blocksMiddle) {
				if (Block->isActive)
				{
					Leftball->BallColisionBlock(Block);
					Rightball->BallColisionBlock(Block);
				}

				Block->Draw(window);
				Block->Update();
				
			}
			//check if the blocks have been deactivated and if so transitions to the next game state

			inactiveBlocksMiddle = 0;
			for (int i = 0; i < blocksMiddle.size(); i++)
			{
				if (blocksMiddle[i]->isActive == false) {
					inactiveBlocksMiddle++;
				}

			}
			inactiveBlocksSide = 0;
			for (int i = 0; i < blocksLeft.size(); i++)
			{
				if (blocksRight[i]->isActive == false) {
					inactiveBlocksSide++;
				}
				if (blocksLeft[i]->isActive == false) {
					inactiveBlocksSide++;
				}
			}
			if (inactiveBlocksMiddle == blocksMiddle.size()) {
				
				gamestates = start;
			}
			if (inactiveBlocksSide == blocksLeft.size() + blocksRight.size()) {
				gamestates = start;
			}
			
			//update and draw the game objects
			player.Draw(window);
			Leftball->Update();
			Leftball->BallColisionPlayer(player);
			Leftball->Draw(window);
			Rightball->Update();
			Rightball->BallColisionPlayer(player);
			Rightball->Draw(window);
			window.display();
			
			
		

			break;
		default:
			break;
		}
	}
	
	return 0;
}


