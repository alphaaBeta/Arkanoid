#pragma once
#include <iostream>	//TODO;???

const int SCREEN_WIDTH = 520;
const int SCREEN_HEIGHT = 480;

const int BLOCK_WIDTH = 40;
const int BLOCK_HEIGHT = 16;

//Gamefield

const int FIELD_WIDTH = SCREEN_WIDTH / BLOCK_WIDTH;
const int FIELD_HEIGHT = SCREEN_HEIGHT / BLOCK_HEIGHT;


const int RACKET_LENGTH = 120;
//const int RACKET_THICKNESS = 8;
const double RACKET_SPEED = 500;

//Ball

#define BALL_LIMIT 20

//Block

#define REGULAR_BLOCK_HEALTH 1
#define STRONG_BLOCK_HEALTH 3
#define VERY_STRONG_BLOCK_HEALTH 100
#define INDESTRUCTIBLE_BLOCK_HEALTH 0

//Powerups

#define POWERUP_COLLECT_RANGE 0.5

#define TRIPLE_PWUP_BALL_NUMBER 3
#define BIGBALL_PWUP_RADIUS_MULTIPLER 2
#define EXTRALIVE_PWUP_LIVE_AMT 1
#define BIGRACKET_PWUP_INCRASE 1.4
#define SMALLRACKET_PWUP_DECRASE 0.6
#define FASTBALL_PWUP_INCRASE 1.5
#define SLOWBALL_PWUP_DECRASE 0.5

enum BlockType { REGULAR, STRONG, VERY_STRONG, INDESTRUCTIBLE };


struct Colour {
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 0;
};