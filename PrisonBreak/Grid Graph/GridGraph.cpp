#include "GridGraph.h"

GridGraph::GridGraph(){}

GridGraph::GridGraph(int R, int C)
{
	M.resize(R);
	for (int i = { 0 }; i < R; ++i)
	{
		M[i].resize(C, { 0 });
	}
}

void GridGraph::ReadGrid(ifstream &Reader)
{
	int r = { 0 }, c = { 0 };
	Reader >> r >> c;
	M.resize(r);
	for (int i = 0; i < r; ++i)
	{
		M[i].resize(c);
		for (int j = 0; j < c; j++)
		{
			Reader >> M[i][j];
		}
	}
}

ostream& operator<<(ostream&, GridGraph &GG)
{
	for (int i = 0; i < GG.M.size(); i++)
	{
		for (int j = 0; j < GG.M[0].size(); j++)
		{
			if (GG.M[i][j] == 45)
			{
				cout << "- ";
			}
			else
			{
				cout << GG.M[i][j] << " ";
			}			
		}
		cout << endl;
	}
	return cout << endl;
}

int& GridGraph::operator () (int R, int C)
{
	return M[R][C];
}

int GridGraph::RowSize()
{
	return M.size();
}

int GridGraph::ColumnSize()
{
	return M[0].size();
}

GridGraph::~GridGraph()
{
}
