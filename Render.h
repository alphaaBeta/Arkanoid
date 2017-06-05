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
#include "Enemy.h"



/**
* \brief Texture wrapper class
*/
class LTexture
{
public:
	
	/**
	* \brief Initializes variables
	*/
	LTexture();

	
	/**
	* \brief Deallocates memory
	*/
	~LTexture();

	
	/**
	* \brief Loads image at specified path
	*/
	bool loadFromFile(std::string path);

#ifdef _SDL_TTF_H

	/**
	* \brief Creates image from font string
	*/
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif


	/**
	* \brief Deallocates texture
	*/
	void free();

	
	/**
	* \brief Set color modulation
	*/
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	
	/**
	* \brief Set blending
	*/
	void setBlendMode(SDL_BlendMode blending);

	
	/**
	* \brief Set alpha modulation
	*/
	void setAlpha(Uint8 alpha);

	
	/**
	* \brief Renders texture at given point
	*/
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	
	/**
	* \brief Gets image dimensions
	*/
	int getWidth();
	int getHeight();

private:
	
	/**
	* \brief The actual hardware texture
	*/
	SDL_Texture* mTexture;


	/**
	* \brief Image dimensions
	*/
	int mWidth;
	int mHeight;
};




/**
* \brief The application time based timer
*/
class LTimer
{
public:
	
	/**
	* \brief Initializes variables
	*/
	LTimer();

	
	/**
	* \brief The various clock actions
	*/
	void start();
	void stop();
	void pause();
	void unpause();

	
	/**
	* \brief Gets the timer's time
	*/
	Uint32 getTicks();


	/**
	* \brief Checks the status of the timer
	*/
	bool isStarted();
	bool isPaused();

private:
	
	/**
	* \brief The clock time when the timer started
	*/
	Uint32 mStartTicks;

	
	/**
	* \brief The ticks stored when the timer was paused
	*/
	Uint32 mPausedTicks;

	
	/**
	* \brief The timer status
	*/
	bool mPaused;
	bool mStarted;
};

/**
* \brief Class containing some methods and texture pointers for rendering.
*/
class Render {
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

	
	/**
	* \brief Scene textures
	*/
	LTexture gBallTexture;
	LTexture gBlockTexture;
	LTexture gRacketTexture;
	LTexture gRacketTexture2;
	LTexture gPwupTexture;
	LTexture gBulletTexture;
	LTexture gTextTexture;
	LTexture gEnemyTexture;

	TTF_Font *gFont = 0;

	Mix_Chunk *gPing = NULL;
	Mix_Chunk *gRacketPong = NULL;

	static void RenderBalls();
	static void RenderBlocks();
	static void RenderRacket();
	static void RenderPwups();
	static void RenderBullets();
	static void RenderEnemies();

};


/**
* \brief Starts up SDL and creates window
*/
bool init();


/**
* \brief Loads media
*/
bool loadMedia();


/**
* \brief Frees media and shuts down SDL
*/
void close();

/**
* \brief Handles input (eg. from keyboard)
*/
void handleInput(SDL_Event &);