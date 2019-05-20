#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <iterator>
#include <exception>

#include <queue>
#include <stack>

// TODO: реализовать функции обхода графа +
// TODO: протестировать функции на предмет корректности +


//#define BFS

#define DFS


using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;
using std::map;
using std::iterator;

using std::queue;
using std::stack;

vector<vector<int>> readMatrix(string filename, bool isOriented = false); // чтение матрицы
map<int, vector<int>> readList(string filename, bool isOriented = false); // чтение списка (формат [1..n])

void showList(map<int, vector<int>>); // отображение списка
void showMatrix(vector<vector<int>>); // отображение матрицы

vector<vector<int>> makeRelMatrix(map<int, vector<int>>); // построение матрицы инциндентности
vector<vector<int>> makeRelMatrix(vector<vector<int>>); // -//-

void showRelMatrix(vector<vector<int>> rel, bool ORIENTED);

bool listWidth(int, map<int, vector<int>>); // обход списка в ширину
bool matrixWidth(int, vector<vector<int>>); // обход матрицы в ширину

bool listDepth(int, map<int, vector<int>>); // обход списка в глубину
bool matrixDepth(int, vector<vector<int>>); // обход матрицы в глубину

bool _matrix = false, _list = false;
vector<vector<int>> matrix;
map<int, vector<int>> list;

//#define ORIENTED false

int main(int argC, char** argV)
{
	bool ORIENTED = false;
	int m;
	cout << "Choose mode:" << endl << "1. Oriented" << endl << "2. Not oriented" << endl;

	cin >> m;
	if (m == 1)
		ORIENTED = true;
	else if (m == 2)
		ORIENTED = false;

	int mode = 0;
	cout << "Choose mode:" << endl << "1. Matrix" << endl << "2. List" << endl;
	cin >> mode;
	switch (mode)
	{
	case 1: // Matrix
	{
		_matrix = true;
		int n = 0;
		matrix = readMatrix("matrix.txt", ORIENTED);
		showMatrix(matrix);
		if (ORIENTED == false)
		{
			cout << "Enter num between 1 and " << matrix.size() << " : ";
			cin >> n;
			if (n < 1 || n > matrix.size())
			{
				cout << "Wrong parameter. Switched to 1." << endl;
				n = 1;
			}

#ifdef BFS
			cout << "BFS" << endl;
			matrixWidth(n, matrix);
#endif
#ifdef DFS
			cout << "DFS" << endl;
			matrixDepth(n, matrix);
#endif
		}
		showRelMatrix(makeRelMatrix(matrix), ORIENTED); // вывод матрицы инциндентности
	}
		break;
	case 2: // List
	{
		_list = true;
		int n = 0;
		list = readList("list.txt", ORIENTED);
		showList(list);
		if (ORIENTED == false)
		{
			cout << "Enter num between 1 and " << list.size() << " : ";
			cin >> n;
			if (n < 1 || n > list.size())
			{
				cout << "Wrong parameter. Switched to 1." << endl;
				n = 1;
			}
#ifdef BFS
			cout << "BFS" << endl;
			listWidth(n, list);
#endif
#ifdef DFS
			cout << "DFS" << endl;
			listDepth(n, list);
#endif
		}

		showRelMatrix(makeRelMatrix(list), ORIENTED); // вывод матрицы инциндентности
	}
		break;
	default:
		return -1;
	}

	system("pause");


	// TODO: заполнить main


	// TODO : реализовать функции:
	// чтение +
	// вывод +
	// рассчёт матрицы +
	// обход +
	// вывод обхода на экран +


	return 0;
}

vector<vector<int>> readMatrix(string filename, bool isOriented)
{
	std::ifstream file;
	file.open(filename);
	vector<int> buf;
	int _buf;
	while (!file.eof())
	{
		file >> _buf;
		buf.push_back(_buf);
	}
	int n = (int)sqrt(buf.size());
	vector<vector<int>> result(n);
	for (int i = 0; i < n; i++)
		result[i] = vector<int>(n);
	int c = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(result[i][j] <= 0)
				result[i][j] = buf[c];
			if (!isOriented && result[j][i] <= 0)
				result[j][i] = buf[c];
			c++;
		}
	}
	file.close();
	return result;
}

map<int, vector<int>> readList(string filename, bool isOriented)
{
	std::ifstream file;
	file.open(filename);
	int _buf1, _buf2;
	map<int, vector<int>> result;
	while (!file.eof())
	{
		file >> _buf1;
		_buf1--;
		file >> _buf2;
		_buf2--;

		result[_buf1].push_back(_buf2);
		if (!isOriented)
			result[_buf2].push_back(_buf1);
	}
	return result;
}

void showList(map<int, vector<int>> list)
{
	cout << endl;
	for (map<int, vector<int>>::iterator i = list.begin(); i != list.end(); i++)
	{
		cout << (*i).first + 1 << " : ";
		for (int j = 0; j < (*i).second.size(); j++)
		{
			cout << (*i).second[j] + 1 << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void showMatrix(vector<vector<int>> matrix)
{
	cout << endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<int>> makeRelMatrix(map<int, vector<int>> Map)
{
	int max = 0;
	map<int, vector<int>>::iterator it;
	for (it = Map.begin(); it != Map.end(); it++)
	{
		if ((*it).first > max)
			max = (*it).first;
	}
	max++;
	vector<vector<int>> relMatrix(max);
	for (int i = 0; i < max; i++)
	{
		relMatrix[i] = vector<int>(max);
	}

	// TODO: сделать заполнение таблицы
	for (it = Map.begin(); it != Map.end(); it++)
	{
		for (int i = 0; i < (*it).second.size(); i++)
		{
			relMatrix[(*it).first][(*it).second[i]] = 1;
			if (relMatrix[(*it).second[i]][(*it).first] != -1 && relMatrix[(*it).second[i]][(*it).first] != 1)
				relMatrix[(*it).second[i]][(*it).first] = -1;
			else
				relMatrix[(*it).second[i]][(*it).first] = 1;
		}
	}

	return relMatrix;
}

vector<vector<int>> makeRelMatrix(vector<vector<int>> Array)
{
	vector<vector<int>> Buf = Array;
	for (int i = 0; i < Buf.size(); i++)
	{
		for (int j = 0; j < Buf[i].size(); j++)
		{
			if (Buf[i][j] > 0)
			{
				Buf[i][j] = 1;
				if (j > i && Buf[j][i] <= 0)
				{
					Buf[j][i] = -1;
				}
			}
		}
	}
	return Buf;
}

void showRelMatrix(vector<vector<int>> rel, bool ORIENTED)
{
	struct pair
	{
		int v1, v2;
		char ch;
	} p;
	vector<pair> m;
	char c = 'a';
	if (_matrix)
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if (ORIENTED)
				{
					if (i != j && matrix[i][j])
					{
						p.v1 = i;
						p.v2 = j;
						p.ch = c++;
						m.push_back(p);
					}
				}
				else
				{
					if (i != j && matrix[i][j] && j > i)
					{
						p.v1 = i;
						p.v2 = j;
						p.ch = c++;
						m.push_back(p);
					}
				}
			}
		}
	}
	if (_list)
	{
		map<int, vector<int>>::iterator i;
		for (i = list.begin(); i != list.end(); i++)
		{
			for (int j = 0; j < (*i).second.size(); j++)
			{
				if (ORIENTED)
				{
					p.v1 = (*i).first;
					p.v2 = (*i).second[j];
					p.ch = c++;
					m.push_back(p);
				}
				else
				{
					if ((*i).second[j] > (*i).first)
					{
						p.v1 = (*i).first;
						p.v2 = (*i).second[j];
						p.ch = c++;
						m.push_back(p);
					}
				}
			}
		}
	}
	cout << endl << "    a b c d e f" << endl;
	for (int i = 0; i < rel.size(); i++)
	{
		cout << i + 1 << " : ";
		for (int j = 0; j < m.size(); j++)
		{
			if (ORIENTED)
			{
				if (m[j].v1 == i)
					cout << "1 ";
				else
					cout << "0 ";
			}
			else
			{
				if (m[j].v1 == i || m[j].v2 == i)
					cout << "1 ";
				else
					cout << "0 ";
			}
		}
		cout << endl;
	}
}

bool listWidth(int n, map<int, vector<int>> list) // обход списка в ширину
{
	if (n < 1 || n > list.size())
		throw std::exception("bad argument");
	n--;
	queue<int> q;
	vector<bool> used(list.size());
	q.push(n);
	while (!q.empty())
	{
		int v = q.front();

		std::cout << v + 1 << " ";

		used[v] = true;
		q.pop();
		for (int i = 0; i < list[v].size(); i++)
		{
			if (!used[list[v][i]])
			{
				q.push(list[v][i]);
				used[list[v][i]] = true;
			}
		}
	}

	std::cout << std::endl;

	return false;
}

bool listDepth(int n, map<int, vector<int>> list) // обход списка в глубину
{
	if (n < 1 || n > list.size())
		throw std::exception("bad argument");
	n--;

	vector<bool> used(list.size());

	stack<int> st;
	st.push(n);

	while (!st.empty())
	{
		int cur = st.top();
		st.pop();
		while (used[cur] == true && !st.empty())
		{
			cur = st.top();
			st.pop();
		}
		if(!used[cur])
			cout << cur + 1 << " ";
		used[cur] = true;
		for (int i = 0; i < list[cur].size(); i++)
		{
			if (!used[list[cur][i]])
				st.push(list[cur][i]);
		}
	}

	std::cout << std::endl;

	return false;
}

bool matrixWidth(int n, vector<vector<int>> matrix) // обход матрицы в ширину
{
	if (n < 1 || n > matrix[0].size())
		throw std::exception("bad argument");
	n--;
	queue<int> q;
	vector<bool> used(matrix[0].size());
	q.push(n);
	while (!q.empty())
	{
		int v = q.front();

		std::cout << v + 1 << " ";

		used[v] = true;
		q.pop();
		for (int i = 0; i < matrix[v].size(); i++)
		{
			if (!used[i] && matrix[v][i])
			{
				q.push(i);
				used[i] = true;
			}
		}
	}

	std::cout << std::endl;

	return false;
}

bool matrixDepth(int n, vector<vector<int>> matrix) // обход матрицы в глубину 
{
	if (n < 1 || n > matrix[0].size())
		throw std::exception("bad argument");
	n--;
	vector<bool> used(matrix[0].size());

	stack<int> st;
	st.push(n);

	while (!st.empty())
	{
		int cur = st.top();
		st.pop();
		while (used[cur] == true && !st.empty())
		{
			cur = st.top();
			st.pop();
		}
		if(!used[cur])
			cout << cur + 1 << " ";
		used[cur] = true;
		for (int i = 0; i < matrix.size(); i++)
			if (matrix[cur][i] > 0 && cur != i && !used[i])
				st.push(i);
	}

	std::cout << std::endl;

	return false;
}
