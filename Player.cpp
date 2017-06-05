#include "Player.h"
#include "Enemy.h"

using json = nlohmann::json;



int FileOp::LoadLevel(int n) {

	std::ifstream f;

	try {
		f.open("levels.json");	//throws FAILURE exception

		//if (!f.good() || !f.is_open()) throw "Error with opening file 'level.json'!";
		
		json l;
		f >> l;
		//we won't be needing the file anymore
		f.close();

		//Create a correct label for each level
		std::string level = "level" + std::to_string(n);
		
		for (int i = 0; i < l[level].size(); i++) {
			json aux = l[level];
			for (int j = 0; j < aux[i].size(); j++) {
				//int testt = aux[i][j];
				GameField::getInstance().AddBlock(j, i, l[level][i][j]);
			}
		}



		return 1;
	}

	catch (std::ios_base::failure ff) {
		std::cerr << ff.what() << std::endl;
		if (f.is_open()) f.close();
		return 0;
	}
}


int FileOp::SaveGame(SaveData save) {

	std::ofstream f;
	try {
		
		f.open(SAVENAME);
		//if (!f.good() || !f.is_open()) throw "Error with creating/opening savefile!";
		save.LoadFromPlayer();

		f << save;

		f.close();
		return 1;

	}
	catch (std::ios_base::failure ff) {
		std::cerr << ff.what() << std::endl;
		if (f.is_open()) f.close();
		return 0;

	}

}

SaveData FileOp::LoadGame() {
	std::ifstream f;

	try {

		f.open(SAVENAME);	
		//if (!f.good() || !f.is_open()) throw "Error with creating/opening savefile!";
		SaveData save;

		f >> save;

		f.close();
		return save;

	}
	catch(std::ios_base::failure ff) {
		std::cerr << ff.what() << std::endl;
		if (f.is_open()) f.close();
		SaveData save = { 1, 0, 1, 1 };
		return save;
	}

}

//increment the argument for next level
int Player::LoadLevel(int n)
{
	
	level = n;
	scoreAtStart = score;
	livesAtStart = lives;

	//Remove blocks
	GameField::getInstance().PurgeBlocks();

	//Remove balls
	while (!Ball::ballList.empty() && Ball::ballList[0]) {
		delete Ball::ballList[0];
	}
	if (!Ball::ballList.empty()) Ball::ballList.clear();

	while (!Enemy::enemyList.empty() && Enemy::enemyList[0] ) {
		delete Enemy::enemyList[0];
	}

	if (FileOp::LoadLevel(level)) {
		Ball::AddBall();
		return 1;
	}
		

	else return 0;
}

int Player::LoadGame() {

	SaveData save = FileOp::LoadGame();

	level = save.level;
	score = save.score;
	lives = save.lives;
	difficulty = save.difficulty;

	LoadLevel(level);

	return 1;
}

int Player::SaveGame() {

	SaveData save;
	save.LoadFromPlayer();

	if (FileOp::SaveGame(save)) return 1;
	return 0;
}