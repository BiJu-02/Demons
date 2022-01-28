#include "Map.h"


Map::Map(std::string map_name)
{
	std::string temp;
	int n, j = 1;
	std::string::size_type sz;
	map_file_path = "assets/";
	map_file_path.append(map_name);
	map_file_path.append(".png");
	map_instruct_file.open(map_file_path);
	getline(map_instruct_file, temp);
	n = std::stoi(temp);
	path_instruct = new int[2 * n + 1];
	path_instruct[0] = n;
	for (int i = 1; i < n; i++)
	{
		getline(map_instruct_file, temp);
		path_instruct[j++] = stoi(temp, &sz);
		path_instruct[j++] = stoi(temp.substr(sz + 1));
	}
}
