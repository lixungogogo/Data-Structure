#pragma once
#include <stdio.h>
#include <iostream>
#include <assert.h>
using namespace std;

typedef struct offset
{
	int x;
	int y;
	int dir;
}offset;

class  pos
{
public:
	pos(int a = 0, int b = 0,int c = 0)
		:x(a)
		, y(b)
		, dir(c)
	{}
	int x;
	int y;
	int dir;
};


int GetNum(FILE *fout);
void GetRowCloumn(int& row, int& cloumn);
void InitMaze(int *maze, int &row, int&cloumn);
void PrintMaze(int *maze, int row, int cloumn); 