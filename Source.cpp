#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <time.h>
#include <SDL_ttf.h>//text



//#include "Ball.h"
//#include "Player.h"
//#include "Racket.h"

#include "Block.h"
#include "GameField.h"
#include "Powerup.h"
#include "Missile.h"

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

			std::stringstream textToRender;


			LTimer stepTimer;

			Ball::AddBall();

			//Ball::BallList[0]->MultiplyBalls(3, *(Ball::BallList[0]));

			Colour clr = { 0, 0, 0, 0 };

			for (int i = 0; i < FIELD_WIDTH; i++) {
				GameField::getInstance().AddBlock(i, 0, VERY_STRONG, clr);
			}

			for (int i = 0; i < FIELD_WIDTH; i++) {
				GameField::getInstance().AddBlock(i, 1, STRONG, clr);
			}

			for (int i = 0; i < FIELD_WIDTH; i++) {
				GameField::getInstance().AddBlock(i, 2, STRONG, clr);
			}

			for (int i = 0; i < FIELD_WIDTH; i++) {
				GameField::getInstance().AddBlock(i, 3, REGULAR, clr);
			}
			for (int i = 0; i < FIELD_WIDTH; i++) {
				GameField::getInstance().AddBlock(i, 4, REGULAR, clr);
			}
			for (int i = 0; i < FIELD_WIDTH; i++) {
				GameField::getInstance().AddBlock(i, 5, REGULAR, clr);
			}

			Racket::getInstance().shooting = 0;
			SDL_RenderSetViewport(Render::getInstance().gRenderer, &Render::getInstance().leftViewport);

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

				//Move the racket and ball and check collision
				char how = Ball::MoveBalls(timeStep);
				if (how == 'p') {
					Mix_PlayChannel(-1, Render::getInstance().gRacketPong, 0);
				}
				else if (how == 'x') {
					Mix_PlayChannel(-1, Render::getInstance().gPing, 0);
				}
				Racket::getInstance().Move(timeStep);
				Powerup::MoveAll(timeStep);
				Missile::MoveAll(timeStep);

				stepTimer.start();

				//Clear screen
				SDL_SetRenderDrawColor(Render::getInstance().gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Render::getInstance().gRenderer);

				//gBallTexture.render(10, 10);


				//Render ball and racket
				Render::RenderBalls();
				Render::RenderBlocks();
				Render::RenderPwups();
				Render::RenderBullets();
				Render::RenderRacket();

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
