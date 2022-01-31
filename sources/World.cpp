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
	slot = -1;
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


	if (is_playing)
	{
		spawn_enemy();
		sprite_list_trav();
		// fighting mechanism
		for (int i = 0; i < 6; i++)
		{
			if (hero_arr[i])
			{
				if (hero_arr[i]->name == "range" && hero_arr[i]->in_fight())
				{
					// adding projectiles to sprite_list
					if (hero_arr[i]->is_blast())
					{
						// initialize projectile with coordinates
						sprite_list.push_back(new Projectile(1200, 280, 0, 80, 80, proj, 3, hero_arr[i]));
						hero_arr[i]->blast_done();
					}
				}
				if (hero_arr[i]->name == "melee" && hero_arr[i]->is_ded)
				{
					hero_arr[i]->release_targets();
				}
			}
		}

	}
	sprite_list.sort([](Game_Obj* a, Game_Obj* b) { return a->yscrn < b->yscrn; });
}

void World::spawn_enemy()
{
	int id;
	if (!enemy_batch.empty())
	{
		if (spawn_tm_intrvl > 5)
		{
			sprite_list.push_back(new Enemy(0, 520, 0, 80, 80, enemy, enemy_batch.back(), map.path_instruct_x, map.path_instruct_y, map.map_chk_pts));
			//std::cout << enemy_batch.back() << std::endl;
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

// called by event handler
void World::spawn_melee()
{
	// "melee"
	sprite_list.push_back(new Melee(1200, 280, 0, 80, 80, melee, 3));
	hero_arr[slot] = sprite_list.back();
}

void World::spawn_range()
{
	// "range"
	sprite_list.push_back(new Range(1200, 280, 0, 80, 80, range, 4));
	hero_arr[slot] = sprite_list.back();
}

void World::sprite_list_trav()
{
	int enemy_count = 0;
	int dis1[6], dis2[6], temp;
	for (int i = 0; i < 6; i++) { dis1[i] = 90;  dis2[i] = 200; }
	Game_Obj* sprite;
	std::list<Game_Obj*>::iterator iter = sprite_list.begin();
	std::list<Game_Obj*>::iterator end = sprite_list.end();
	while (iter != end)
	{
		sprite = *iter;
		// check from hero_arr the distances of enemies...by checking sprite.name == "enemy"
		// enemy and hero will have intercepted sprites pointer...otherwise null
		if (!sprite->is_active)
		{
			// delete and erase sprite from list
			if (sprite->name == "enemy")
			{
				if (sprite->enemy_passed)
				{ decr_life(sprite->tex_id); }
				else		
				{ coins += sprite->get_reward(); }		// wut abt score..?
				sprite->release_targets();
			}

			iter = sprite_list.erase(iter);
			delete sprite;
			continue;
		}
		else if (sprite->name == "enemy")
		{
			enemy_count++;
			// for loop for hero_arr...coming soon?
			for (int i = 0; i < 6; i++)
			{
				if (hero_arr[i])
				{
					if (!hero_arr[i]->in_fight() && !hero_arr[i]->is_moving)
					{
						// u will know what to do when the time comes...~oogway?
						temp = dist(hero_arr[i]->x2d, hero_arr[i]->y2d, sprite->x2d, sprite->y2d);
						if (hero_arr[i]->name == "range")
						{
							if (dis2[i] > temp)
							{
								dis2[i] = temp;
								hero_arr[i]->set_target(sprite);
							}
						}
						else if (hero_arr[i]->name == "melee")
						{
							if (dis1[i] > temp)
							{
								dis1[i] = temp;
								hero_arr[i]->set_target(sprite);
							}
						}
					}
					
				}
			}
		}
		for (int i = 0; i < 6; i++)
		{
			if (hero_arr[i])
			{
				if (hero_arr[i]->get_target() == sprite)
				{
					if (hero_arr[i]->name == "melee")
					{ sprite->set_target(hero_arr[i]); }
					else if (hero_arr[i]->name == "range")
					{ sprite->set_range_target(hero_arr[i]); }
				}
			}
		}
		iter++;
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
	Game_Obj* temp;
	while (sprite_list.begin() != sprite_list.end())
	{
		temp = sprite_list.back();
		sprite_list.pop_back();
		delete temp;
	}
}

 