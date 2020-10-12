#pragma once
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class GridGraph
{
	vector<vector<int>> M;
public:
	GridGraph();
	GridGraph(int R, int C);
	void ReadGrid(ifstream &Reader);
	friend ostream& operator<<(ostream&, GridGraph &GG);
	int& operator () (int R, int C);
	int RowSize();
	int ColumnSize();
	~GridGraph();
};

