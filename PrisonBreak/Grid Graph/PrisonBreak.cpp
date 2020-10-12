#include<iostream>
#include<stack>
#include<queue>
#include"GridGraph.h"
#include<string>
using namespace std;

//Struct for Storing Positions
struct position
{
	int R;
	int C;
};

bool FindPrisoner(GridGraph &Map, position& Prisoner);
bool PrsonBreakDFS(GridGraph &M, stack<position>& Path);
bool PrisonBreakBFS(GridGraph Map, stack<position>& Path);
bool PrisonBreakExplore(GridGraph &Map, stack<position> &Path, int PR, int PC);
void UpdateMap(GridGraph &Map, stack<position> Path);
void PrintPath(stack<position> Path);
bool FindAllPrisoners(GridGraph &Map, vector<position> &Vs);
void AllPrisonsBreakBFS(GridGraph Map);


//Finctions for Menu 
void PrisionBreak(bool(*f)(GridGraph &Map, stack<position>& Path));
void AllPrisionsBreakUsingBFS();

//Main
void MENU();


int main()
{
	MENU();
	return 0;
}
//Find First Prisoner in Map
bool FindPrisoner(GridGraph &Map, position& Prisoner)
{
	for (int i = 0; i < Map.RowSize(); i++)
	{
		for (int j = 0; j < Map.ColumnSize(); j++)
		{
			if (Map(i,j) == 2)
			{
				Prisoner.R = i;
				Prisoner.C = j;
				return true;
			}
		}
	}
	return false;
}
//Find Path for one Prisoner using DFS (Part 1)
bool PrsonBreakDFS(GridGraph &Map, stack<position>& Path)
{
	position Prisoner;
	FindPrisoner(Map, Prisoner);
	return PrisonBreakExplore(Map, Path, Prisoner.R, Prisoner.C);

}
//Find Path for one Prisoner using BFS (Part 2)
bool PrisonBreakBFS(GridGraph &Map, stack<position>& Path)
{
	queue<position> Qp;
	queue<stack<position>> Qpaths;

	position P;
	stack<position> S;

	if (FindPrisoner(Map, P))
	{
		Qp.push(P);
		Qpaths.push(S);

		while (!Qp.empty())
		{
			P = Qp.front();
			S = Qpaths.front();
			Qp.pop();
			Qpaths.pop();

			int PR = { P.R }, PC = { P.C };

			if (PR >= 0 && PR < Map.RowSize() && PC >= 0 && PC < Map.ColumnSize() && Map(PR, PC) == 3)
			{
				S.push(P);
				while (!S.empty())
				{
					Path.push(S.top());
					S.pop();
				}
				return true;
			}
			else
			if (PR >= 0 && PR < Map.RowSize() && PC >= 0 && PC < Map.ColumnSize() && Map(PR, PC) != 1 && Map(PR, PC) != 4)
			{
				S.push(P);

				Map(PR, PC) = 4; //For Remembering

				P.R = { PR + 1 }, P.C = { PC }; //Down
				Qp.push(P);
				Qpaths.push(S);

				P.R = { PR - 1 }, P.C = { PC }; //Up
				Qp.push(P);
				Qpaths.push(S);

				P.R = { PR }, P.C = { PC + 1 }; //Right
				Qp.push(P);
				Qpaths.push(S);


				P.R = { PR }, P.C = { PC - 1 }; //Left
				Qp.push(P);
				Qpaths.push(S);
			}
		}
	}
	
	return false;
}
//Helper Function for DFS (Part 1)
bool PrisonBreakExplore(GridGraph &Map, stack<position> &Path, int PR, int PC)
{
	if (PR < 0 || PR >= Map.RowSize() || PC < 0 || PC >= Map.ColumnSize())
	{
		return false;
	}

	if (Map(PR, PC) == 1 || Map(PR, PC) == 4) // 1 for wall, 4 for rememmbering line
	{
		return false;
	}

	if (Map(PR, PC) == 3)
	{
		position Prisoner;
		Prisoner.R = PR;
		Prisoner.C = PC;
		Path.push(Prisoner);
		return true;
	}

	Map(PR, PC) = 4;

	bool Found = PrisonBreakExplore(Map, Path, PR + 1, PC)
			  || PrisonBreakExplore(Map, Path, PR - 1, PC)
			  || PrisonBreakExplore(Map, Path, PR, PC + 1)
			  || PrisonBreakExplore(Map, Path, PR, PC - 1);

	if (Found)
	{
		position Prisoner;
		Prisoner.R = PR;
		Prisoner.C = PC;
		Path.push(Prisoner);
	}

	return Found;
}
// Update the Map with Given Path
void UpdateMap(GridGraph &Map, stack<position> Path)
{
	position P;
	while (!Path.empty())
	{
		P = Path.top();
		Path.pop();
		Map(P.R, P.C) = '-';
	}
}
// Print the Given Path
void PrintPath(stack<position> Path)
{
	position P;
	int i = { 1 };
	cout << "\nPath: \n\n";
	while (!Path.empty())
	{
		P = Path.top();
		Path.pop();
		cout << "(" << P.R << "," << P.C << ") -> \t";
		if (i % 3 && i != 0)
		{
			cout << "\n";
		}
		i++;
	}
	cout << "\n\n";
}
//Find All Prisoners in Map
bool FindAllPrisoners(GridGraph &Map, vector<position> &Vs)
{
	for (int i = 0; i < Map.RowSize(); i++)
	{
		for (int j = 0; j < Map.ColumnSize(); j++)
		{
			position Prisoner;
			if (Map(i, j) == 2)
			{
				Prisoner.R = i;
				Prisoner.C = j;
				Vs.push_back(Prisoner);
			}
		}
	}
	if (Vs.size() != 0)
		return true;
	return false;
}
//Find Path for one Prisoner using BFS (Part 3)
bool PrisonBreakBFS(GridGraph Map, stack<position>& Path, position P)
{
	queue<position> Qp;
	queue<stack<position>> Qpaths;

	stack<position> S;

	Qp.push(P);
	Qpaths.push(S);

	while (!Qp.empty())
	{
		P = Qp.front();
		S = Qpaths.front();
		Qp.pop();
		Qpaths.pop();

		int PR = { P.R }, PC = { P.C };

		if (PR >= 0 && PR < Map.RowSize() && PC >= 0 && PC < Map.ColumnSize() && Map(PR, PC) == 3)
		{
			S.push(P);
			while (!S.empty())
			{
				Path.push(S.top());
				S.pop();
			}
			return true;
		}
		else
		if (PR >= 0 && PR < Map.RowSize() && PC >= 0 && PC < Map.ColumnSize() && Map(PR, PC) != 1 && Map(PR, PC) != 4)
		{
			S.push(P);

			Map(PR, PC) = 4; //For Remembering

			P.R = { PR + 1 }, P.C = { PC }; //Down
			Qp.push(P);
			Qpaths.push(S);

			P.R = { PR - 1 }, P.C = { PC }; //Up
			Qp.push(P);
			Qpaths.push(S);

			P.R = { PR }, P.C = { PC + 1 }; //Right
			Qp.push(P);
			Qpaths.push(S);


			P.R = { PR }, P.C = { PC - 1 }; //Left
			Qp.push(P);
			Qpaths.push(S);
		}
	}

	return false;
}
// Find and Print Path of All the Prisoners in the Map (Part 3)
void AllPrisonsBreakBFS(GridGraph Map)
{
	vector<position> Prisoners;
	if (FindAllPrisoners(Map, Prisoners))
	{
		for (int i = 0; i < Prisoners.size(); i++)
		{
			stack<position> Path;
			GridGraph M = Map;
			if (PrisonBreakBFS(Map, Path, Prisoners[i]))
			{
				cout << M;
				UpdateMap(M, Path);
				cout << M;
				PrintPath(Path);
			}
			else
			{
				cout << "\t\t-------------------------------------------" << endl;
				cout << "\t\tPrisoner at location: (" << Prisoners[i].R << "," << Prisoners[i].C << ") can't escape." << endl;
				cout << "\t\t-------------------------------------------" << endl;
			}
		}
	}
}


//Main
void MENU()
{
	int x = { 0 };
	do
	{
		cout << "========================================================" << endl;
		cout << "\t  Enter 1 to Break the Prison using DFS"<<endl;
		cout << "\t  Enter 2 to Break the Prison using BFS" << endl;
		cout << "Enter 3 to Break the Prison for All Prisoners using DFS" << endl;
		cout << "\t\t  Enter 4 to exit" << endl;
		cout << "========================================================" << endl;
		cout << "\t\t      Select: ";
		cin >> x;

		switch (x)
		{
		case 1:
			PrisionBreak(PrsonBreakDFS);
			break;
		case 2:
			PrisionBreak(PrisonBreakBFS);
			break;
		case 3:
			AllPrisionsBreakUsingBFS();
			break;
		case 4:
			break;
		default:
			break;
		}

	} while (x != 4);
}

//Function for menu
void PrisionBreak(bool(*f)(GridGraph &Map, stack<position>& Path))
{
	cout << "\t\t     +++++++++++++" << endl;
	cout << "\t\t     Prision Break" << endl;
	cout << "\t\t     +++++++++++++" << endl;
	GridGraph Map;
	string FileName;
	cout << "\t  Enter File Name to Load Map: ";
	cin >> FileName;
	ifstream fin(FileName);
	if (!fin.is_open())
	{
		cout << "\t\t   --------------" << endl;
		cout << "\t\t   File Not Found" << endl;
		cout << "\t\t   --------------" << endl;
	}
	else
	{
		Map.ReadGrid(fin);
		GridGraph G = Map;
		stack<position> Path;
		(*f)(Map, Path);
		cout << "\t\t\t  ======" << endl;
		cout << "\t\t\t   DONE" << endl;
		cout << "\t\t\t  ======" << endl;
		bool flag = false;
		char x;
		do
		{
			cout << "\t    Enter A to Print Map without Path" << endl;
			cout << "\t  Enter B to Update Map with found Path" << endl;
			cout << "\t      Enter C to Print Map with Path" << endl;
			cout << "\tEnter D to Pint all coordinates of found path" << endl;
			cout << "\t\t      Enter E to Exit" << endl;
			cout << "\t\t\t   Enter: ";
			cin >> x;

			if (x == 'a' || x == 'A')
			{
				cout << G;
			}
			else
			if (x == 'B' || x == 'b')
			{
				flag = true;
				UpdateMap(Map, Path);
				cout << "\t\t\t  ======" << endl;
				cout << "\t\t\t   DONE" << endl;
				cout << "\t\t\t  ======" << endl;
			}
			else
			if (x == 'c' || x == 'C')
			{
				if (flag == true)
					cout << Map;
				else
				{
					cout << "\t\t\t==================" << endl;
					cout << "\t\t\tMap is not Updated" << endl;
					cout << "\t\t\t==================" << endl;
				}
			}
			else
			if (x == 'D' || x == 'd')
			{
				PrintPath(Path);
			}
			else
			if (x == 'E' || x == 'e')
				break;
			else
				continue;
		} while (true);
	}
}

void AllPrisionsBreakUsingBFS()
{
	GridGraph Map;
	string FileName;
	cout << "\t   Enter File Name to Load Map: ";
	cin >> FileName;
	ifstream fin(FileName);
	if (!fin.is_open())
	{
		cout << "\t\t   --------------" << endl;
		cout << "\t\t   File Not Found" << endl;
		cout << "\t\t   --------------" << endl;
	}
	else
	{
		Map.ReadGrid(fin);
		stack<position> Path;
		AllPrisonsBreakBFS(Map);
		cout << "\t\t\t  ======" << endl;
		cout << "\t\t\t   DONE" << endl;
		cout << "\t\t\t  ======" << endl;
	}
	fin.close();
}
