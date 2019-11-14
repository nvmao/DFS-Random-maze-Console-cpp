#include<iostream>
#include <string>
#include "freeLibrary.h"
#include <vector>
#include <stack>
#include <ctime>
using namespace  std;

class Vector2
{
public:
	int x, y;
	Vector2(){}
	Vector2(int x,int y)
	{
		this->x = x, this->y = y;
	}
};

class Wall
{
	char sprite;
	bool open;
	Vector2 position;
	
public:
	Color color = Color::WHITE;
	Wall()
	{
		
	}

	Wall(Vector2 position)
	{
		sprite = char(219);
		open = false;
		this->position = position;
	}
	bool is_open()
	{
		return open;
	}
	void open_wall()
	{
		open = true;
	}

	void draw()
	{
		if(!open)
		{
			gotoxy(position.x, position.y);
			cout << sprite;
		}
		else
		{
			gotoxy(position.x, position.y);
			SetBGColor(color);
			cout << ' ';
			
		}
	}

};

class Grid
{
	Wall walls[4];
	Vector2 position;
	Vector2 add;
	vector<Grid> neight_bours;
	
public:
	Grid *parrent = nullptr;
	Vector2 get_pos()
	{
		return add;
	}
	void set_add(Vector2 a)
	{
		add = a;
	}
	
	Grid()
	{
		
	}
	vector<Grid> get_neight_bours()
	{
		return neight_bours;
	}
	Grid(Vector2 position)
	{
		this->position = position;
		walls[0] = Wall(Vector2(this->position.x - 1, this->position.y));
		walls[1] = Wall(Vector2(this->position.x + 1, this->position.y));
		walls[2] = Wall(Vector2(this->position.x, this->position.y - 1));
		walls[3] = Wall(Vector2(this->position.x, this->position.y + 1));
	}

	void change_color()
	{
		for(int i=  0 ; i < 4;i++)
		{
			walls[i].color = RED;
		}
	}

	void open_wall_left()
	{
		
			walls[0].open_wall();
			walls[0].draw();
		
	}
	void open_wall_right()
	{
		
			walls[1].open_wall();
			walls[1].draw();
		
	}
	void open_wall_up()
	{
		
			walls[2].open_wall();
			walls[2].draw();
		
	}
	void open_wall_down()
	{
		
			walls[3].open_wall();
			walls[3].draw();
		
	}


	void set_neight_bours(Grid grid)
	{
		neight_bours.push_back(grid);
	}
	void delete_neight_bour(int i)
	{
		neight_bours.clear();
	}

	void draw()
	{
		for(int i = 0 ; i < 4;i++)
		{
			walls[i].draw();
		}
		SetBGColor(Color::WHITE);
		gotoxy(position.x, position.y); cout << ' ';
		SetBGColor(0);
	}

};

class Map
{
	Grid grids[30][119];
	bool visited[30][119];
	int height = 30, width = 119;
	stack<Grid> stack;
	int dir_x[4] = { 0,0,2,-2 };
	int dir_y[4] = { 2,-2,0,0 };
public:
	Map()
	{
		for(int i = 2;i < 30;i += 2)
		{
			for(int j = 1 ; j < 119;j+= 2)
			{
				grids[i][j] = Grid(Vector2(j, i));
				grids[i][j].set_add(Vector2(i, j));
				visited[i][j] = false;
			}
		}
	}
	void draw()
	{
		SetColor(Color::BLACK);
		gotoxy(0, 1); cout << string(119, char(219));
		gotoxy(0, 29); cout << string(119, char(219));
		for (int i = 0; i < 29; i++)
		{
			gotoxy(0, 1 + i);
			cout <<  string(119, char(219));
			gotoxy(118, 1 + i);
			cout <<  string(119, char(219));
		}

		for (int i = 2; i < 30; i += 2)
		{
			for (int j = 1; j < 119; j += 2)
			{
				grids[i][j].draw();
			}
		}
		SetColor(7);
	}

	bool can_visited_neightbours(int x,int y)
	{
		for(int i = 0 ; i < 4;i++)
		{
			int newx = x + dir_x[i];
			int newy = y + dir_y[i];

			if (newx < 1 || newx > 28) continue;
			if (newy < 1 || newy > 117) continue;
			if (visited[newx][newy]) continue;

			grids[newx][newy].parrent = &grids[x][y];
			grids[x][y].set_neight_bours(grids[newx][newy]);

		}
		if(grids[x][y].get_neight_bours().empty())
		{
			return false;
		}
		return true;
	}

	void trace_path(Grid *node)
	{
		gotoxy(node->get_pos().y, node->get_pos().x);
		SetColor(Color::RED);
		cout << char(219);
		while(true)
		{
			gotoxy(node->parrent->get_pos().y, node->parrent->get_pos().x);
			SetColor(Color::RED);
			cout << char(219);


			int x = - node->parrent->get_pos().x + node->get_pos().x;
			int y = - node->parrent->get_pos().y + node->get_pos().y;
			node->change_color();
			node->parrent->change_color();
			//left
			if (y == -2 && x == 0)
			{
				node->open_wall_right();
				node->parrent->open_wall_left();
			}
			//right
			if (y == 2 && x == 0)
			{
				node->open_wall_left();
				node->parrent->open_wall_right();
			}
			// up
			if (y == 0 && x == -2)
			{
				node->open_wall_down();
				node->parrent->open_wall_up();
			}
			if (y == 0 && x == 2)
			{
				node->open_wall_up();
				node->parrent->open_wall_down();
			}

			node = node->parrent;
			SetColor(Color::LIGHTGRAY);
			Sleep(100);
			if(node->parrent == nullptr)
			{
				return;
			}
		}
	}

	void Maze_generator()
	{
		Grid current = grids[2][1];
		visited[2][1] = true;

		while(true)
		{
			if (can_visited_neightbours(current.get_pos().x, current.get_pos().y))
			{
				current = grids[current.get_pos().x][current.get_pos().y];

				int random = rand() % current.get_neight_bours().size();

				auto random_neight_bour = current.get_neight_bours()[random];
				current.delete_neight_bour(random);
				//

				int x = random_neight_bour.get_pos().x - current.get_pos().x;
				int y = random_neight_bour.get_pos().y - current.get_pos().y;

				//left
				if(y == -2 && x == 0)
				{
					random_neight_bour.open_wall_right();
					current.open_wall_left();
				}
				//right
				if(y == 2 && x == 0)
				{
					random_neight_bour.open_wall_left();
					current.open_wall_right();
				}
				// up
				if(y ==0 && x == -2)
				{
					random_neight_bour.open_wall_down();
					current.open_wall_up();
				}
				if(y == 0 && x == 2)
				{
					random_neight_bour.open_wall_up();
					current.open_wall_down();
				}
				stack.push(current);
				Sleep(10);

				grids[current.get_pos().x][current.get_pos().y] = current;
				grids[random_neight_bour.get_pos().x][random_neight_bour.get_pos().y] = random_neight_bour;

				current = random_neight_bour;

				visited[current.get_pos().x][current.get_pos().y] = true;


			}
			else
			{
				if (stack.empty())
				{
					trace_path(&grids[28][117]);
					break;
				}
				current = stack.top();
				stack.pop();
			}
		}

		
	}

};

int main()
{
	srand(time(0));
	ShowCursor(false);
	while (true) {
		Map m;
		m.draw();

		m.Maze_generator();
		cin.get();
	}

	cin.get();
}