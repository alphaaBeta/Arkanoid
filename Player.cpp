#include "Player.h"

using json = nlohmann::json;



int FileOp::LoadLevel(int n) {

	std::ifstream f;

	try {
		f.open("levels.json");
		if (!f.good() || !f.is_open()) throw "Blad otwierania pliku 'level.json'!";
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

	catch (std::string a) {
		std::cerr << a << std::endl;
		if (f.is_open()) f.close();
		return 0;
	}
}

int Player::NextLevel()
{
	
	level++;
	lives++;

	//Remove blocks
	GameField::getInstance().PurgeBlocks();

	//Remove balls
	for (int i = 0; i < Ball::ballList.size(); i++)
		delete Ball::ballList[i];
	if (!Ball::ballList.empty()) Ball::ballList.clear();


	if (FileOp::LoadLevel(level)) {
		Ball::AddBall();
		return 1;
	}
		

	else return 0;
}
