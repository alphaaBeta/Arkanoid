#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <time.h>
//#include <SDL_ttf.h>//text



//#include "Ball.h"
//#include "Player.h"
//#include "Racket.h"

#include "Block.h"
#include "GameField.h"
#include "Powerup.h"
#include "Missile.h"



#include "Config.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////


//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};



//The application time based timer
class LTimer
{
public:
	//Initializes variables
	LTimer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;
};



//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gBallTexture;
LTexture gBlockTexture;
LTexture gRacketTexture;
LTexture gRacketTexture2;
LTexture gPwupTexture;
LTexture gBulletTexture;

Mix_Chunk *gPing = NULL;
Mix_Chunk *gRacketPong = NULL;
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////



LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

LTimer::LTimer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void LTimer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}


#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
return mHeight;
}

/////////////////////////////////////////////////////

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load ball texture
	if (!gBallTexture.loadFromFile("resources/ball.png"))
	{
		printf("Failed to load ball texture!\n");
		success = false;
	}

	//Load Block texture
	if (!gBlockTexture.loadFromFile("resources/block.png"))
	{
		printf("Failed to load block texture!\n");
		success = false;
	}

	//Load Racket texture
	if (!gRacketTexture.loadFromFile("resources/racket-1.bmp") || !gRacketTexture2.loadFromFile("Resources/racket-2.bmp"))
	{
		printf("Failed to load racket textures!\n");
		success = false;
	}

	//Load Pwup texture
	if (!gPwupTexture.loadFromFile("resources/pwup.bmp")) {
		printf("Failed to load pwup texture!\n");
		success = false;
	}

	//Load bullet texture
	if (!gBulletTexture.loadFromFile("resources/bullet.bmp")) {
		printf("Failed to load bullet texture!\n"); 
		success = false;
	}


	//Load sound effects
	gPing = Mix_LoadWAV("resources/ping.wav");
	if (gPing == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gRacketPong = Mix_LoadWAV("resources/racket.wav");
	if (gRacketPong == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gBallTexture.free();
	gBlockTexture.free();
	gRacketTexture.free();

	Mix_FreeChunk(gPing);
	Mix_FreeChunk(gRacketPong);
	gPing = 0;
	gRacketPong = 0;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

//Render all the balls
void RenderBalls() {

	int i;
	for (i = 0; i < (Ball::BallList).size(); i++) {
		SDL_Rect ballRect = { 0, 0 };
		ballRect.w = (Ball::BallList)[i]->radius * 2;
		ballRect.h = (Ball::BallList)[i]->radius * 2;
		gBallTexture.render(int((Ball::BallList)[i]->x - (Ball::BallList)[i]->radius), int((Ball::BallList)[i]->y - (Ball::BallList)[i]->radius), &ballRect);

	}
}

//Render all the blocks
void RenderBlocks() {

	int i;
	//Rectangle alllows to resize texture
	SDL_Rect blockRect = { 0, 0 };
	blockRect.w = BLOCK_WIDTH;
	blockRect.h = BLOCK_HEIGHT;

	for (i = 0; i < (GameField::BlockList).size(); i++) {
		Colour clr = { GameField::getInstance().BlockList[i]->colour };
		//Setting colour and alpha of texture, before rendering the correct block
		gBlockTexture.setColor(clr.r, clr.g, clr.b);
		gBlockTexture.setAlpha(clr.a);
		gBlockTexture.render(int((GameField::BlockList)[i]->x), int((GameField::BlockList)[i]->y), &blockRect);

	}
}

//Render the racket
void RenderRacket() {

	SDL_Rect rackRect = { 0, 0 };
	rackRect.w = int((Racket::getInstance()).width);
	rackRect.h = 8;

	//regular texture
	if(!Racket::getInstance().shooting)
	gRacketTexture.render(int((Racket::getInstance()).x - ((Racket::getInstance()).width / 2)),
							int((Racket::getInstance()).y),
							&rackRect);
	//if shooting powerup is up
	else if(Racket::getInstance().shooting == 1)
		gRacketTexture2.render(int((Racket::getInstance()).x - ((Racket::getInstance()).width / 2)),
			int((Racket::getInstance()).y),
			&rackRect);
}

//Render powerups
void RenderPwups() {

	SDL_Rect Rect = { 0, 0 };
	Rect.w = 12;
	Rect.h = 12;
	Colour clr;

	for (int i = 0; i < GameField::getInstance().PowerupList.size(); i++) {
		clr = GameField::getInstance().PowerupList[i]->color;
		gPwupTexture.setColor(clr.r, clr.g, clr.b);
		gPwupTexture.setAlpha(clr.a);
		gPwupTexture.render(GameField::getInstance().PowerupList[i]->x,\
			GameField::getInstance().PowerupList[i]->y,
			&Rect);
	}
	
}

//Render bullets
void RenderBullets() {

	SDL_Rect Rect = { 0,0 };
	Rect.w = 3;
	Rect.h = 10;

	Colour clr = { 255, 0, 0, 255 };

	for (int i = 0; i < Missile::MissileList.size(); i++) {
		gBulletTexture.setColor(clr.r, clr.g, clr.b);
		gBulletTexture.setAlpha(clr.a);

		gBulletTexture.render(\
			Missile::MissileList[i]->x - 1,
			Missile::MissileList[i]->y,
			&Rect);
	}
}

void handleInput(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: Racket::getInstance().speed -= RACKET_SPEED; break;
		case SDLK_RIGHT: Racket::getInstance().speed += RACKET_SPEED; break;
		case SDLK_UP: 
			if ((Racket::getInstance()).shooting) {
				Missile *aux = new Missile((Racket::getInstance()).x, (Racket::getInstance()).y);
			}
		}
	}

	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: Racket::getInstance().speed += RACKET_SPEED; break;
		case SDLK_RIGHT: Racket::getInstance().speed -= RACKET_SPEED; break;
		}

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////



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

			//which key was pressed last

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
					Mix_PlayChannel(-1, gRacketPong, 0);
				}
				else if (how == 'x') {
					Mix_PlayChannel(-1, gPing, 0);
				}
				Racket::getInstance().Move(timeStep);
				Powerup::MoveAll(timeStep);
				Missile::MoveAll(timeStep);

				stepTimer.start();

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//gBallTexture.render(10, 10);


				//Render ball and racket
				RenderBalls();
				RenderBlocks();
				RenderPwups();
				RenderBullets();
				RenderRacket();

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
