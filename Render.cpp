#include "Render.h"




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
		newTexture = SDL_CreateTextureFromSurface(Render::getInstance().gRenderer, loadedSurface);
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
	SDL_Surface* textSurface = TTF_RenderText_Solid(Render::getInstance().gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(Render::getInstance().gRenderer, textSurface);
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
	SDL_RenderCopyEx(Render::getInstance().gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
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
		Render::getInstance().gWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH+SIDEBAR_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Render::getInstance().gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			Render::getInstance().gRenderer = SDL_CreateRenderer(Render::getInstance().gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (Render::getInstance().gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(Render::getInstance().gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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
	if (!Render::getInstance().gBallTexture.loadFromFile("resources/ball.png"))
	{
		printf("Failed to load ball texture!\n");
		success = false;
	}

	//Load Block texture
	if (!Render::getInstance().gBlockTexture.loadFromFile("resources/block.png"))
	{
		printf("Failed to load block texture!\n");
		success = false;
	}

	//Load Racket texture
	if (!Render::getInstance().gRacketTexture.loadFromFile("resources/racket-1.bmp") || !Render::getInstance().gRacketTexture2.loadFromFile("resources/racket-2.bmp") ) 
	{
		printf("Failed to load racket textures!\n");
		success = false;
	}

	//Load Pwup texture
	if (!Render::getInstance().gPwupTexture.loadFromFile("resources/pwup.bmp")) {
		printf("Failed to load pwup texture!\n");
		success = false;
	}

	//Load bullet texture
	if (!Render::getInstance().gBulletTexture.loadFromFile("resources/bullet.bmp")) {
		printf("Failed to load bullet texture!\n");
		success = false;
	}

	//Load enemy texture
	if (!Render::getInstance().gEnemyTexture.loadFromFile("resources/enemy.bmp")) {
		printf("Failed to load enemy texture!\n");
		success = false;
	}

	//Load sound effects
	Render::getInstance().gPing = Mix_LoadWAV("resources/ping.wav");
	if (Render::getInstance().gPing == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	Render::getInstance().gRacketPong = Mix_LoadWAV("resources/racket.wav");
	if (Render::getInstance().gRacketPong == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load font
	Render::getInstance().gFont = TTF_OpenFont("resources/arial.ttf", 28);
	if (Render::getInstance().gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };

	}

	return success;
}

void close()
{
	//Free loaded images
	Render::getInstance().gBallTexture.free();
	Render::getInstance().gBlockTexture.free();
	Render::getInstance().gRacketTexture.free();
	Render::getInstance().gPwupTexture.free();
	//Free font texture
	Render::getInstance().gTextTexture.free();

	//Free global font
	TTF_CloseFont(Render::getInstance().gFont);
	Render::getInstance().gFont = NULL;

	Mix_FreeChunk(Render::getInstance().gPing);
	Mix_FreeChunk(Render::getInstance().gRacketPong);
	Render::getInstance().gPing = 0;
	Render::getInstance().gRacketPong = 0;

	//Destroy window	
	SDL_DestroyRenderer(Render::getInstance().gRenderer);
	SDL_DestroyWindow(Render::getInstance().gWindow);
	Render::getInstance().gWindow = NULL;
	Render::getInstance().gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();

}

//Render all the balls
void Render::RenderBalls() {

	int i;
	for (i = 0; i < (Ball::ballList).size(); i++) {
		SDL_Rect ballRect = { 0, 0 };
		ballRect.w = (Ball::ballList)[i]->radius * 2;
		ballRect.h = (Ball::ballList)[i]->radius * 2;
		Render::getInstance().gBallTexture.render(int((Ball::ballList)[i]->x - (Ball::ballList)[i]->radius), int((Ball::ballList)[i]->y - (Ball::ballList)[i]->radius), &ballRect);

	}
}

//Render all the blocks
void Render::RenderBlocks() {

	int i;
	//Rectangle alllows to resize texture
	SDL_Rect blockRect = { 0, 0 };
	blockRect.w = BLOCK_WIDTH;
	blockRect.h = BLOCK_HEIGHT;

	for (i = 0; i < (GameField::blockList).size(); i++) {
		Colour clr = { GameField::getInstance().blockList[i]->colour };
		//Setting colour and alpha of texture, before rendering the correct block
		Render::getInstance().gBlockTexture.setColor(clr.r, clr.g, clr.b);
		Render::getInstance().gBlockTexture.setAlpha(clr.a);
		Render::getInstance().gBlockTexture.render(int((GameField::blockList)[i]->x), int((GameField::blockList)[i]->y), &blockRect);

	}
}

//Render the racket
void Render::RenderRacket() {

	SDL_Rect rackRect = { 0, 0 };
	rackRect.w = int((Racket::getInstance()).width);
	rackRect.h = 8;

	//regular texture
	if (!Racket::getInstance().shooting)
		Render::getInstance().gRacketTexture.render(int((Racket::getInstance()).x - ((Racket::getInstance()).width / 2)),
			int((Racket::getInstance()).y),
			&rackRect);
	//if shooting powerup is up
	else if (Racket::getInstance().shooting == 1)
		Render::getInstance().gRacketTexture2.render(int((Racket::getInstance()).x - ((Racket::getInstance()).width / 2)),
			int((Racket::getInstance()).y),
			&rackRect);
}

//Render powerups
void Render::RenderPwups() {

	SDL_Rect Rect = { 0, 0 };
	Rect.w = 12;
	Rect.h = 12;
	Colour clr;

	for (int i = 0; i < GameField::getInstance().powerupList.size(); i++) {
		clr = GameField::getInstance().powerupList[i]->color;
		Render::getInstance().gPwupTexture.setColor(clr.r, clr.g, clr.b);
		Render::getInstance().gPwupTexture.setAlpha(clr.a);
		Render::getInstance().gPwupTexture.render(\
			int(GameField::getInstance().powerupList[i]->x), \
			int(GameField::getInstance().powerupList[i]->y), \
			&Rect);
	}

}

//Render bullets
void Render::RenderBullets() {

	SDL_Rect Rect = { 0,0 };
	Rect.w = 3;
	Rect.h = 10;

	Colour clr = { 255, 0, 0, 255 };

	for (int i = 0; i < Missile::missileList.size(); i++) {
		Render::getInstance().gBulletTexture.setColor(clr.r, clr.g, clr.b);
		Render::getInstance().gBulletTexture.setAlpha(clr.a);

		Render::getInstance().gBulletTexture.render(\
			Missile::missileList[i]->x - 1,
			Missile::missileList[i]->y,
			&Rect);
	}
}

//Render enemies
void Render::RenderEnemies() {
	SDL_Rect Rect = { 0,0 };
	Rect.w = ENEMY_SIZE * 2;
	Rect.h = ENEMY_SIZE * 2;

	for (int i = 0; i < Enemy::enemyList.size(); i++) {
		Colour clr = { Enemy::enemyList[i]->colour };

		Render::getInstance().gEnemyTexture.setColor(clr.r, clr.g, clr.b);
		Render::getInstance().gEnemyTexture.setAlpha(clr.a);
		Render::getInstance().gEnemyTexture.render(int(Enemy::enemyList[i]->x - Enemy::enemyList[i]->size), int(Enemy::enemyList[i]->y - Enemy::enemyList[i]->size), &Rect);

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
		case SDLK_s: Player::getInstance().SaveGame();
			break;
		case SDLK_l: Player::getInstance().LoadGame();
			break;
		case SDLK_f: for (int i = 0; i < Enemy::enemyList.size(); i++) Enemy::enemyList[i]->Act();
			break;
		case SDLK_1: new EnemyDiagonal(SCREEN_WIDTH/2);
			break;
		case SDLK_2: new EnemyShooting(SCREEN_WIDTH / 2);
			break;
		case SDLK_3: new EnemyGroupper(SCREEN_WIDTH / 2);
			break;
		case SDLK_4: new EnemyBlocker(SCREEN_WIDTH / 2);
			break;

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