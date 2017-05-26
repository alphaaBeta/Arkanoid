#include "Player.h"

using json = nlohmann::json;



int FileOp::LoadLevel(int n) {

	std::fstream filee;

	try {
		std::ifstream f("levels.json");
		if (!f.good() || !f.is_open()) throw "Blad otwierania pliku 'level.json'!";
		json l;
		f >> l;
		//we won't be needing the file anymore
		f.close();

		//Todo for level n
		level test;
		test.nO = 1;
		auto aux = l["level1"];
		for (int i = 0; i < aux.size(); i++) {	//iterate to size of vectorarray
			test.blocks.push_back(aux[i]);	//push a vector at the end of vectorarray
		}
		//Now we can set the actualy block array

		for (int i = 0; i < test.blocks.size(); i++) {
			for (int j = 0; j < test.blocks[i].size(); j++) {
				GameField::getInstance().AddBlock(j, i, test.blocks[i][j]);
			}
		}



		return 1;
	}

	catch (std::string a) {
		std::cerr << a << std::endl;
		if (filee.is_open()) filee.close();
		return 0;
	}
}

int Player::NextLevel()
{
	level++;
	if(FileOp::LoadLevel(level)) return 1;

	else return 0;
}
