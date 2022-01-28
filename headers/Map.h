#pragma once

#include <string>
#include <fstream>


class Map
{
public:
	int* path_instruct;
	std::string map_file_path;
	std::ifstream map_instruct_file;

	Map(std::string map_name);

};