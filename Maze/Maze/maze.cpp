#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <stack>
#include "maze.h"
#define M 7
#define N 7
using namespace std;
void PrintMaze(int Maze[M][N])
{
	for (int m = 0; m < M; m++)
	{
		for (int n = 0; n < N; n++)
			cout << Maze[m][n] << " ";
		cout << endl;
	}
	cout << endl;
}
bool maze(int s_x,int s_y,int e_x,int e_y,int Maze[M][N])
{
	offset pos(s_x,s_y);
	int Mark[M][N] = { 0 };
	Mark[s_x][s_y] = 1;
	stack<offset> s;
	s.push(pos);
	PrintMaze(Maze);
	while (!s.empty())
	{
		int i = pos._dir;
		for (; i < 8; i++)
		{
			if (Maze[pos._x + Dir[i]._x][pos._y + Dir[i]._y] == 0 && Mark[pos._x + Dir[i]._x][pos._y + Dir[i]._y] == 0)
			{
				pos._dir = i;//标记方向，下次从没有走过的方向判断
				break;
			}
		}
		if (i == 8)	//没有通路
		{
			s.pop();
			pos = s.top();//出栈，退回上一步
			//pos._dir++;
		}
		else//有通路，将上一步压栈，再走一步
		{
			pos._x += Dir[i]._x;
			pos._y += Dir[i]._y;
			s.push(pos);
			Mark[pos._x][pos._y] = 1;//走过的路标记为1
			pos._dir = 0;
		}
		if (pos._x == e_x &&pos._y == e_y)
		{
			PrintMaze(Mark);
			return true;
		}
	}
	return false;
}

int main()
{
	int m[7][7] = {1,1,1,1,1,1,1,0,0,1,0,0,0,1,1,1,0,0,1,1,1,1,0,1,1,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	bool success = maze(1, 0, 3, 6, m);
	return 0;
}