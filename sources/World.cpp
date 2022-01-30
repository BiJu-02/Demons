#include "World.h"

World::World() : map(Map("map"))
{
	// load all sprite textures


	// temporary shit

}

void World::start_game()
{
	score = 0;
	lives = 20;
	coins = 100;
	no_of_heroes = 0;
	for (int i=0; i<max_heroes; i++)
	{ hero_arr[i] = NULL; }
	wave_no = 0;
	batch_size = 0;
	enemy_on_map = false;
	is_paused = false;
	is_playing = false; // should be false...true only after play button is pressed
}

// at the end of updates sort the forward list of sprites
void World::update()
{
	for (auto sprite : sprite_list)
	{ sprite->update(); }

	sprite_list_trav();

	if (is_playing)
	{
		// enemy spawning...time intervals and all mangaging too
		// fighting mechanism
		// checking number of enemies on map after entire batch has been dispatched
		spawn_enemy();
	}
	// destroy inactive sprite ...if (!sprite.is_active) 
	sprite_list.sort([](Game_Obj* a, Game_Obj* b) { return a->yscrn < b->yscrn; });
}

void World::spawn_enemy()
{
	std::string s = "enemy";
	int id;
	if (!enemy_batch.empty())
	{
		if (spawn_tm_intrvl > 5)
		{
			sprite_list.push_back(new Enemy(0, 520, 0, 80, 80, s, enemy_batch.back(), map.path_instruct_x, map.path_instruct_y, map.map_chk_pts));
			enemy_batch.pop_back();
			std::cout << sprite_list.size() << std::endl;
			spawn_tm_intrvl = 0;
		}
		else
		{ spawn_tm_intrvl += spawn_tm_qtm; }
	}
	else if (!enemy_on_map)
	{
		srand(time(0));
		wave_no++;
		batch_size += 5;
		int tmp_batch = batch_size;
		spawn_tm_intrvl = 0;
		while (tmp_batch > 1)
		{
			if (tmp_batch > 20)
			{
				// all
				id = rand() % 100;
				if (id < 75)
				{
					enemy_batch.push_back(0);
					tmp_batch -= 1;
				}
				else if (id < 95)
				{
					enemy_batch.push_back(1);
					tmp_batch -= 10;
				}
				else
				{
					enemy_batch.push_back(2);
					tmp_batch -= 20;
				}
			}
			else if (tmp_batch > 10)
			{
				// mid and low
				id = rand() % 100;
				if (id < 75)
				{
					enemy_batch.push_back(0);
					tmp_batch -= 1;
				}
				else
				{
					enemy_batch.push_back(1);
					tmp_batch -= 10;
				}
			}
			else
			{
				// low
				enemy_batch.push_back(0);
				tmp_batch -= 1;
			}
		}
	}

}

void World::sprite_list_trav()
{
	int enemy_count = 0;
	std::list<Game_Obj*>::iterator iter = sprite_list.begin();
	std::list<Game_Obj*>::iterator end = sprite_list.end();
	while (iter != end)
	{
		Game_Obj* sprite = *iter;
		// check from hero_arr the distances of enemies...by checking sprite.name == "enemy"
		// enemy and hero will have intercepted sprites pointer...otherwise null
		if (!sprite->is_active)
		{
			// delete and erase sprite from list
			if (sprite->enemy_passed)
			{ decr_life(sprite->tex_id); }
			iter = sprite_list.erase(iter);
			delete sprite;
		}
		else if (sprite->name == "enemy")
		{
			enemy_count++;
			// for loop for hero_arr...coming soon?
			for (int i = 0; i < no_of_heroes; i++)
			{
				// u will know what to do when the time comes...~oogway?

			}

			iter++;
		}

	}
	if (enemy_count)
	{ enemy_on_map = true; }
	else
	{ enemy_on_map = false; }
}

void World::decr_life(int id)
{
	if (id == 2)
	{ lives -= 20; }
	else if (id == 1)
	{ lives -= 10; }
	else
	{ lives -= 1; }
}

void World::sprite_create()
{

}

void World::sprite_destroy()
{

}

void World::exit_game()
{
	// delete and remove elements in sprite list
}

 