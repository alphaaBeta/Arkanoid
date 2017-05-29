#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <time.h>
#include <SDL_ttf.h>//text
#include <typeinfo>



//#include "Ball.h"
//#include "Player.h"
//#include "Racket.h"

#include "Block.h"
#include "GameField.h"
#include "Powerup.h"
#include "Missile.h"
#include "Enemy.h"

#include "Render.h"



#include "Config.h"


//The window we'll be rendering to




#undef main

int main(int argc, char* argv[])
{

	srand(time(NULL));
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//aux string to use SDL function rendering TTF
			std::stringstream textToRender;

			//used to set speed
			LTimer stepTimer;
			

			//Loads nextlevel (level1)
			Player::getInstance().NextLevel();

			
			SDL_RenderSetViewport(Render::getInstance().gRenderer, &Render::getInstance().leftViewport);

			Enemy *test = new EnemyDiagonal;
			Enemy *test2 = new EnemyDiagonal;
			Enemy *test3 = new EnemyShooting;

			Enemy::enemyList;

			//Enemy::GetInst<EnemyDiagonal>();
			std::vector<Enemy*> testt = Enemy::GetInst<EnemyDiagonal>();
			std::vector<Enemy*> testt3 = Enemy::GetInst<EnemyDiagonal, EnemyShooting>();

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the racket
					handleInput(e);
				}

				float timeStep = stepTimer.getTicks() / 1000.f;

				//Move everything
				char how;
				{
					how = Ball::MoveBalls(timeStep);
					Racket::getInstance().Move(timeStep);
					Powerup::MoveAll(timeStep);
					Missile::MoveAll(timeStep);
					//Enemy::MoveAll(timeStep);
				}

				//Proceed to next level if board is clear
				if (GameField::getInstance().IsClear())
					Player::getInstance().NextLevel();

				//Play sounds, for ball
				//Bounce from pallet
				if (how == 'p') {
					Mix_PlayChannel(-1, Render::getInstance().gRacketPong, 0);
				}
				//Bounce from block/whatever
				else if (how == 'x') {
					Mix_PlayChannel(-1, Render::getInstance().gPing, 0);
				}

				//Measurin how long does it take to render(to go through the loop
				stepTimer.start();

				//Clear screen
				SDL_SetRenderDrawColor(Render::getInstance().gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Render::getInstance().gRenderer);


				//Render everything
				{
					Render::RenderBalls();
					Render::RenderBlocks();
					Render::RenderPwups();
					Render::RenderBullets();
					Render::RenderRacket();
					//Render::RenderEnemies();
				}

				//Rendering right interface
				SDL_RenderSetViewport(Render::getInstance().gRenderer, &Render::getInstance().rightViewport);

				{
					SDL_Rect border = { 0, 0, 10, SCREEN_HEIGHT };
					SDL_SetRenderDrawColor(Render::getInstance().gRenderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_RenderFillRect(Render::getInstance().gRenderer, &border);

					SDL_Color textColour = { 0,0,0 };
					textToRender.str("");
					textToRender << "Level: " << Player::getInstance().level;
					Render::getInstance().gTextTexture.loadFromRenderedText(textToRender.str().c_str(), textColour);

					Render::getInstance().gTextTexture.render(10, 0);

					textToRender.str("");
					textToRender << "Lives: " << Player::getInstance().lives;
					Render::getInstance().gTextTexture.loadFromRenderedText(textToRender.str().c_str(), textColour);

					Render::getInstance().gTextTexture.render(10, 80);

					textToRender.str("");
					textToRender << "Score: " << Player::getInstance().score;
					Render::getInstance().gTextTexture.loadFromRenderedText(textToRender.str().c_str(), textColour);

					Render::getInstance().gTextTexture.render(10, 120);
				}


				//Set viewport back to left one
				SDL_RenderSetViewport(Render::getInstance().gRenderer, &Render::getInstance().leftViewport);
				
				//Update screen
				SDL_RenderPresent(Render::getInstance().gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
