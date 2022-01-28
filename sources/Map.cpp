#include "Map.h"
//#include <iostream>


Map::Map(std::string map_name)
{
	std::string temp;
	int n;
	map_file_path = "assets/map_path/";
	map_file_path.append(map_name);
	map_file_path.append(".txt");
	map_instruct_file.open(map_file_path);
	map_instruct_file >> temp;
	map_instruct_file.ignore();
	n = std::stoi(temp);
	map_chk_pts = n;
	path_instruct_x = new int[n];
	path_instruct_y = new int[n];
	for (int i = 0; i < n; i++)
	{
		map_instruct_file >> temp;
		map_instruct_file.ignore();
		path_instruct_x[i] = stoi(temp);
		map_instruct_file >> temp;
		map_instruct_file.ignore();
		path_instruct_y[i] = stoi(temp);
	}
}
