#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

const int N = 10;

const int NUM_SHIPS = 10;

void cursorxy (int x, int y) //				sets console cursor according to coordinates x, y
{
	COORD p = {x, y};
	SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), p);
}

bool ship_in_map (int x, int y, int dir, int size_ship)
{
	bool in_map = 1;
	//										checking if ship is within the borders of the map
	for (int i = 0; i < size_ship; i ++)
	{
		if (x < 0 || y < 0 || x >= N || y >= N)
		{
			in_map = 0;
			break;
		}
		
		switch (dir)
		{
			case 0:
				x ++;
			break;
			case 1:
				y ++;
			break;
			case 2:
				x --;
			break;
			case 3:
				y --;
			break;
		}
	}
	
	return in_map;
}
	//										randomly generating and placing ships
void place_rand_ships (int map [N][N], int size_ship, int ship_id)
{
	int x, y;
		
	int dir = 0;
	
	int count_ship = 0;
	
	int count_tact = 0;                                                                                     
	
	while (count_ship < 1)
	{//										ship generation
		count_tact ++;
		
		if (count_tact > 1000)
		{
			break;
		}
		//									the starting point of a ship
		x = rand () % N;
		y = rand () % N;			
		//									choosing placement direction
		dir = rand () % 4;
		
		int temp_x = x;
		int temp_y = y;
		
		bool placement_is_possible = 1;
		//									checking the possibility of placing a ship
		for (int i = 0; i < size_ship; i ++)
		{
			if (x < 0 || y < 0 || x >= N || y >= N)
			{
				placement_is_possible = 0;
				break;
			}

			if (map [x][y] >= 1)
			{
				placement_is_possible = 0;
				break;
			}
			
			if (y < N - 1)
				if (map[x    ][y + 1] >= 1)
				{
					placement_is_possible = 0;
					break;	
				}
			
			if (y > 0)
				if (map[x    ][y - 1] >= 1)
				{
					placement_is_possible = 0;
					break;	
				}
			
			if (x < N - 1)
				if (map[x + 1][y    ] >= 1)
				{
					placement_is_possible = 0;
					break;	
				}
			
			if (x < N - 1 && y < N - 1)
				if (map[x + 1][y + 1] >= 1)
				{
					placement_is_possible = 0;
					break;	
				}
			
			if (x < N - 1 && y > 0)
				if (map[x + 1][y - 1] >= 1)
				{
					placement_is_possible = 0;
					break;	
				}
			
			if (x > 0)
				if (map[x - 1][y    ] >= 1)
				{
					placement_is_possible = 0;
					break;	
				}
			
			if (x > 0 && y < N - 1)
				if (map[x - 1][y + 1] >= 1)
				{
					placement_is_possible = 0;
					break;	
				}
			
			if (x > 0 && y > 0)
				if (map[x - 1][y - 1] >= 1)
				{
					placement_is_possible = 0;
					break;	
				}
			
			switch (dir)
			{
				case 0:
					x ++;
				break;
				case 1:
					y ++;
				break;
				case 2:
					x --;
				break;
				case 3:
					y --;
				break;
			}
		}
		//									if placement is possible, placing the ship
		if (placement_is_possible == 1)
		{
			x = temp_x;
			y = temp_y;
			
			for (int i = 0; i < size_ship; i ++)
			{
				map [x][y] = ship_id;
				
				switch (dir)
				{
					case 0:
						x ++;
					break;
					case 1:
						y ++;
					break;
					case 2:
						x --;
					break;
					case 3:
						y --;
					break;
				}
			}
			
			count_ship ++;
		}
	}
}

void show_ships_status (int ships [NUM_SHIPS+1], int x, int y)
{	
    int ships_temp [NUM_SHIPS + 1] = {0};
    
	for(int i = 1; i <= NUM_SHIPS; i ++)
	{
        ships_temp [i] = ships [i];
	}
	
	int x_temp = x; int y_temp = y;
	
	for (int i = 1; i <= 4  ; i ++)
	{
		cursorxy (x_temp * 2, 0 + y_temp++);
		
		int N = 0;
		int k = 4;
		
		for (int j = 1; j <= NUM_SHIPS ; j ++)
		{
			if (j == 2 || j == 4 || j == 7 && k > 1)
			{
				k--;
			}
			 
			if (ships_temp [j] != k && ships_temp [j] != 0)
			{
				ships_temp [j] = k;
			}
			
			if (ships_temp [j] == i)
			{
				N++;
			}
		}
		
		cout << N ; 
	}
	
	x_temp = x, y_temp = y;
	
	cursorxy ( (x + 1) * 2, y + 3);
	cout << "- ####";
	cursorxy ( (x + 1) * 2, y + 2);
	cout << "- ###";
	cursorxy ( (x + 1) * 2, y + 1);
	cout << "- ##";
	cursorxy ( (x + 1) * 2, y + 0);
	cout << "- #";
}

//											console map output
void map_show (int map [N][N], int mask [N][N],  bool use_mask, int x, int y)
{

	cursorxy (x * 2, y);
	cout << ' ' << ' ';
	
	for (int i = 0; i < N; i ++)
	{
		cout << i << " ";
	}
	
	cout << endl;
	
	for (int i = 0; i < N; i ++)
	{
		cursorxy (x * 2, 1 + y ++);
		cout << i << " ";
		
		for (int j = 0; j < N; j ++)
		{
			if (mask [j][i] == 1 || use_mask == 0)				// Mask layer
			{									//
				if (map [j][i] == 0 || map [j][i] <= -4)
				{
					cout << ' ';
				}
				else if (map [j][i] == -1)
				{
					cout << 'X';
				}
				else if (map [j][i] == -2)
				{
					cout << "o";
				}
				else
				{
					cout << '#';
				}
			}
			else
			{
				cout << ' ';
			}
			
			cout << ( (i == 0 && j == 9) ? " x": " ");
		}
		
		cout << endl;
	}
	
	cursorxy (x*2, 1+y);
	cout << "  y" << endl;
}

int shoot (int map [N][N], int x, int y, int ships[NUM_SHIPS+1], int mask [N][N])
{
	int result = 0; 
	
	if (map [x][y] == -1 || map [x][y] == -2)
	{
		result = 3; //shoot again
	}
	else if (map [x][y] >= 1)
	{
		ships [map [x][y] ] --;
		
		if (ships [map [x][y] ] <= 0)
		{
			result = 2; //destroyed
		}
		else
		{
			result = 1; //hit
		}
		
		if (y < N - 1)
			if (map [x    ][y + 1] == 0 || (map [x    ][y + 1] <= -10 && map [x    ][y + 1] >= -20) )
			{
				map [x    ][y + 1] = map [x][y] - 20;
			}
		
		if (y > 0)
			if (map [x    ][y - 1] == 0 || (map [x    ][y - 1] <= -10 && map [x    ][y - 1] >= -20) )
			{
				map [x    ][y - 1] = map [x][y] - 20;
			}
		
		if (x < N - 1)
			if (map [x + 1][y    ] == 0 || (map [x + 1][y    ] <= -10 && map [x + 1][y    ] >= -20) )
			{
				map [x + 1][y    ] = map [x][y] - 20;
			}
		
		if (x < N - 1 && y < N - 1)
			if (map [x + 1][y + 1] == 0 || (map [x + 1][y + 1] <= -10 && map [x + 1][y + 1] >= -20) )
			{
				map [x + 1][y + 1] = map [x][y] - 20;
			}
		
		if (x < N - 1 && y > 0)
			if (map [x + 1][y - 1] == 0 || (map [x + 1][y - 1] <= -10 && map [x + 1][y - 1] >= -20) )
			{
				map [x + 1][y - 1] = map [x][y] - 20;
			}
		
		if (x > 0)
			if (map [x - 1][y    ] == 0 || (map [x - 1][y    ] <= -10 && map [x - 1][y    ] >= -20) )
			{
				map [x - 1][y    ] = map [x][y] - 20;
			}
		
		if (x > 0 && y < N - 1)
			if (map [x - 1][y + 1] == 0 || (map [x - 1][y + 1] <= -10 && map [x - 1][y + 1] >= -20) )
			{
				map [x - 1][y + 1] = map [x][y] - 20;	
			}
		
		if (x > 0 && y > 0)
			if (map [x - 1][y - 1] == 0 || (map [x - 1][y - 1] <= -10 && map [x - 1][y - 1] >= -20) )
			{
				map [x - 1][y - 1] = map [x][y] - 20;
			}
		
		map [x][y] = -1; //(marking hit ship)
		
	}
	else
	{
		map [x][y] = -2; //(miss)
	}
	
	mask [x][y] = 1;
	
	return result;
}

int main ()
{
	srand (time (NULL) );
	
	while (true)
	{
		int count_ship = 0;
		
		int map [N][N] = {0};
		int map2 [N][N] = {0};
		
		int ships [NUM_SHIPS+1] = {0, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
		int ships2 [NUM_SHIPS+1] = {0, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
		
		int mask [N][N] = {0};
		int mask2 [N][N] = {0};
		
		//									generating and placing random ships
		for (int i = 1; i <= NUM_SHIPS; i ++)
		{
			place_rand_ships (map, ships[i], i);
		}
		
		for (int i = 1; i <= NUM_SHIPS; i ++)
		{
			place_rand_ships (map2, ships2[i], i);
		}
		
		//									console map output & main game cycle & messages to the player
		
		int temp_hit;
		int first_hit_x = 0;
		int first_hit_y = 0;
		
		int mode = 0;
		
		int x = 0;
		int y = 0;
		int x_bot = 0;
		int y_bot = 0;
		
		int dir = 0;
		
		vector <int> dirs;
		
		dirs.push_back (3);
		dirs.push_back (2);
		dirs.push_back (1);
		dirs.push_back (0);
		
		bool win_player = 0;
		bool win_bot = 0;
		
		bool turn = 1;
		
		while (win_player == false && win_bot == false) //while no one won
		{
			int resultshoot = 0;
			
			do
			{	
				cursorxy (26*2, 0); cout << "Your ships:";
				cursorxy (26*2, 6); cout << "Enemy ships:";
				
				show_ships_status (ships, 2*N+6, 1);
				show_ships_status (ships2, 2*N+6, 7);
				
				map_show (map, mask, 0, 0, 0);
				map_show (map2, mask2, 1, N + 3, 0);
							
				if (turn == 1) //if player moves
				{
					cout << endl << "Input coordinates: ";
						
					cin >> x >> y;
					
					temp_hit = map2 [x][y] - 20;
					
					resultshoot = shoot (map2, x, y, ships2, mask2);
					
					if (resultshoot == 1)
					{
						cout << "\t\t   Hit!" << endl;
					}
					else if (resultshoot == 2)
					{	
						bool dead = 1;
						
						for (int i = 1; i <= NUM_SHIPS; i++ ) //checking if all ships are sunk for game result
						{
							if (ships2[i] != 0)
							{
								dead = 0;
								break;
							}
						}
						if (dead == 1)
						{
							win_player = 1;
							break;
						}
						
						cout << "\t\t   Ship destroyed!" << endl;
						
						for (int i = 0; i < N ; i ++)
						{
							for (int j = 0; j < N; j++)
							{
								if (map2 [i][j] == temp_hit)
								map2 [i][j] = -2;
								if (map2 [i][j] == -2)
								mask2 [i][j] = 1;
							}	
						}
					}
					else
					{
						cout << "\t\t   Miss." << endl;
					}
				}
				else
				{
					cout << endl << "Computer's turn:  ";
					
					if (mode == 0)
					{
						do
						{
							x_bot = rand () % N;
							y_bot = rand () % N;
														
							resultshoot = shoot (map, x_bot, y_bot, ships, mask);
						} while (resultshoot == 3);
						
						if (resultshoot == 1)
						{
							Sleep(1000);
							
							cout << x_bot << " " << y_bot << endl;

							mode = 1;
							
							first_hit_x = x_bot;
							first_hit_y = y_bot;
														
							if (! dirs.empty() )
							{
								dir = dirs[dirs.size() - 1];
								dirs.pop_back();
							}

							cout << "\t\t  Hit!" << endl;
						}
						else if (resultshoot == 2)
						{
							Sleep(1000);
							
							cout << x_bot << " " << y_bot << endl;

							bool dead = 1;
						
							for (int i = 1; i <= NUM_SHIPS; i++ )
							{
								if (ships[i] != 0)
								{
									dead = 0;
									break;
								}
							}
							if (dead == 1)
							{
								win_bot = 1;
								break;
							}
							
							cout << "\t\t  Ship destroyed!" << endl;
							
							for (int i = 0; i < N ; i ++)
							{
								for (int j = 0; j < N; j++){
									if (map [i][j] <= -4)
									map [i][j] = -2;
								}	
							}
							
						}
						else
						{
							Sleep(1000);
							
							cout << x_bot << " " << y_bot << endl;
														
							cout << "\t\t  Miss." << endl;
						}
					}
					else if (mode == 1)
					{
						bool change_dir = 0;
						
						if (dir == 0) // to the left
						{
							if (x_bot > 0)
							{
								x_bot --;
							}
							else
							{
								change_dir = 1;
							}
						}
						else if (dir == 1) // to the right
						{
							if (x_bot < N - 1)
							{
								x_bot ++;
								
							}
							else
							{
								change_dir = 1;
							}
						}
						else if (dir == 2) // upward
						{
							if (y_bot > 0)
							{
								y_bot --;
							}
							else
							{
								change_dir = 1;
							}
						}
						else if (dir == 3) // downward
						{
							if (y_bot < N - 1)
							{
								y_bot ++;
								
							}
							else
							{
								change_dir = 1;
							}
						}
						
						if (map [x_bot][y_bot] == -2) change_dir = 1;
						
						if (change_dir == 1)
						{
							if (! dirs.empty() )
							{
								dir = dirs[dirs.size() - 1];
								dirs.pop_back();
							}
														
							x_bot = first_hit_x;
							y_bot = first_hit_y;
							
							continue;
						}
												
						resultshoot = shoot (map, x_bot, y_bot, ships, mask);
						
						if (resultshoot == 1)
						{
							Sleep(1000);
							
							cout << x_bot << " " << y_bot << endl;
							
							cout << "\t\t  Hit!" << endl;
						}
						else if (resultshoot == 2)
						{	
							mode = 0;
							
							dirs.clear();
							
							dirs.push_back (3);
							dirs.push_back (2);
							dirs.push_back (1);
							dirs.push_back (0);
							
							bool dead = 1;
						
							for (int i = 1; i <= NUM_SHIPS; i++ )
							{
								if (ships[i] != 0)
								{
									dead = 0;
									break;
								}
							}
							if (dead == 1)
							{
								win_bot = 1;
								break;
							}
							
							Sleep(1000);
							
							cout << x_bot << " " << y_bot << endl;
							
							cout << "\t\t  Ship destroyed!" << endl;
							
							for (int i = 0; i < N ; i ++)
							{
								for (int j = 0; j < N; j ++){
									if (map [i][j] <= -4)
									map [i][j] = -2;
								}	
							}
						}
						else
						{
							if (! dirs.empty() )
							{
								dir = dirs[dirs.size() - 1];
								dirs.pop_back();
							}
							
							Sleep(1000);
							
							cout << x_bot << " " << y_bot << endl;
							
							cout << "\t\t  Miss." << endl;
							
							x_bot = first_hit_x;
							y_bot = first_hit_y;
							
						}						
					}
				}
				
				if (turn != 1)
				{
					Sleep (3000);	//Sleep () function suspends the execution of the program for a specified period of time
				}
				else Sleep (1000);
				
				system ("cls"); 	//system ("cls"); asks Windows OS to clear the console screen
				
			} while (resultshoot != 0); //do, while the one who moves doesn't make a miss 
			
			turn = !turn;
		}
		
		if (win_player)
		{
			cout << "\t\t   You win!!!" << endl;
		}
		else
		{
			cout << "\t\t  You lose." << endl;
		}
		
		cursorxy(26*2, 0); cout << "Your ships:";
		cursorxy(26*2, 6); cout << "Enemy ships:";
		
		show_ships_status (ships, 26, 1);
		show_ships_status (ships2, 26, 7);
		
		map_show (map, mask, 0, 0, 0);
		map_show (map2, mask2, 1, 13, 0);
		
		getch ();				//getch (); halts the execution of program till any character input is given by the user
	}

	system ("pause");           //system ("pause"); asks Windows OS to pause the program execution until you press a key
	
	return 0;
}
