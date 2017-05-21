#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

#include "Ball.h"
#include "Racket.h"
#include "Block.h"
#include "GameField.h"
#include "Missile.h"


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


class Render {//singleton
private:
	Render() {	}
	Render(const Render&) { }
public:

	static Render& getInstance() {

		static Render instance;
		return instance;

	}

	SDL_Window* gWindow = NULL;

	SDL_Renderer* gRenderer = NULL;

	SDL_Rect leftViewport = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect rightViewport = { SCREEN_WIDTH + 1, 0, SCREEN_WIDTH + SIDEBAR_WIDTH, SCREEN_HEIGHT };

	//Scene textures
	LTexture gBallTexture;
	LTexture gBlockTexture;
	LTexture gRacketTexture;
	LTexture gRacketTexture2;
	LTexture gPwupTexture;
	LTexture gBulletTexture;
	LTexture gTextTexture;

	TTF_Font *gFont = 0;

	Mix_Chunk *gPing = NULL;
	Mix_Chunk *gRacketPong = NULL;

	static void RenderBalls();
	static void RenderBlocks();
	static void RenderRacket();
	static void RenderPwups();
	static void RenderBullets();

};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window renderer




void handleInput(SDL_Event &);