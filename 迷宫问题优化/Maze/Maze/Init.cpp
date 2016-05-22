#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "maze.h"
using namespace std;

int GetNum(FILE *fout)
{
	int num = 0;
	int ret = 0;
	char ch = '0';
	ch = fgetc(fout);
	if (ch == '\n')
		return -1;
	if (ch >= '0' && ch <= '9')
		ret = 1;
	else ret = 0;
	while (ret == 1)
	{
		num = num * 10 + ch - '0';
		ch = fgetc(fout);
		if (ch == '1' || ch == '0')
			ret = 1;
		else ret = 0;
	}
	return num;
}
void GetRowCloumn(int& row, int& cloumn)
{
	FILE *fout = fopen("maze.txt", "r");
	assert(NULL != fout);
	row = GetNum(fout);
	cloumn = GetNum(fout);
}
void InitMaze(int *maze, int &row, int&cloumn)
{
	assert(maze);
	int i = 0, j = 0;
	FILE *fout = fopen("maze.txt", "r");
	assert(NULL != fout);
	char ch = fgetc(fout);
	while (ch != '\n')
	{
		ch = fgetc(fout);
	}
	while (i < cloumn)
	{
		j = 0;
		ch = fgetc(fout);
		while (ch != '\n')
		{
			if (ch == '1' || ch == '0')
			{
				if (maze[i*row + j] != 3)
				{
					maze[i*row + j] = ch - '0';
					j++;
				}
			}
			ch = fgetc(fout);
		}
		i++;
	}
	fclose(fout);
}

void PrintMaze(int *maze, int row, int cloumn)
{
	assert(maze);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < cloumn; j++)
			cout << maze[i*row + j] << " ";
		cout << endl;
	}
	cout << endl;
} 