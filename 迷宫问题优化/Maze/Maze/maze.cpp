#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <stack>
#include "maze.h"
using namespace std;

offset Dir[4] = { { 0, -1, 0 }, { 1, 0, 1 }, 
{ 0, 1, 2 } ,{ -1, 0, 3 }  };
bool Get(pos out, pos In,int row, int cloumn)
{
	if (out.x != In.x && out.y != In.y)
	{
		if (out.x == 0 || out.x == cloumn - 1 || out.y == 0 || out.y == row - 1)
		{
			return true;
		}
	}
	return false;
}
bool Maze(int *maze, int row, int cloumn, pos In, stack<pos>& s, int &size)
{
	assert(maze);
	s.push(In);
	pos cur = In;
	while (!s.empty())
	{
		int i = 0;
		for (i = cur.dir; i < 4; i++)
		{
			int x = cur.x + Dir[i].x;
			int y = cur.y + Dir[i].y;
			if (x < 0 || x >= row || y < 0 || y >= cloumn)
			{
				continue;
			}
			int& value = maze[y * cloumn + x];
			if (value == 0)
			{
				if (s.top().x == In.x && s.top().y == In.y && s.top().dir == In.dir)
				{
					s.top().dir = i;
				}
				cur.x =x;
				cur.y =y;
				cur.dir = i;
  				s.push(cur);
				cur.dir = 0;
				value = 2;
				size++;
				break;
			}
		}
		if (i == 4)
		{
			cur = s.top();
			s.pop();
			size--;
		}
		else if (Get(s.top(),In, row, cloumn))
		{
			if (maze[s.top().y*cloumn + s.top().x] == 2)
			return true;
		}
	}
	return false;
}
bool BestMaze(int *maze, int row, int cloumn, pos In)
{
	stack<pos> s;
	stack<pos> min;
	int size = 0;
	int m = row*cloumn;
	while (Maze(maze, row, cloumn, In, s, size))
	{
		PrintMaze(maze, row, cloumn);
		InitMaze(maze, row, cloumn);
		maze[s.top().y*cloumn + s.top().x] = 3;
		if (size < m)
		{
			m = size;
			size = 0;
			min = s;
		}
		while (!s.empty())
			s.pop();
	}
	if (m != row*cloumn)
		return true;
	return false;
}
int main()
{
	int row = 0, cloumn = 0;
	GetRowCloumn(row, cloumn);
	int *maze = new int[row*cloumn];
	InitMaze(maze,row,cloumn);
	PrintMaze(maze,row,cloumn);
	pos In(0, 1);
	stack<pos> s;
	bool ret = BestMaze(maze, row, cloumn, In);
	PrintMaze(maze, row, cloumn);
	return 0;
}