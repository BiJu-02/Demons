#pragma once

#include <string>
#include <fstream>


class Map
{
public:
	int *path_instruct_x, *path_instruct_y;
	int map_chk_pts;
	std::string map_file_path;
	std::ifstream map_instruct_file;

	Map(std::string map_name);

};