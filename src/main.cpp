#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "beatmap.h"

int main(size_t argc, char **argv) {
	if (argc < 2) return 1;

	std::string inname(argv[1]);
	std::ifstream fin(inname);
	Randomizer::Beatmap beatmap(fin);
	fin.close();

	beatmap.arrange();

	if (argc == 2) {
		std::cout << beatmap.toJson(true) << std::endl;
		system("pause");
	}
	else {
		std::string outname(argv[2]);
		std::ofstream fout(outname);
		fout << beatmap.toJson(true);
		fout.close();
	}

	return 0;
}