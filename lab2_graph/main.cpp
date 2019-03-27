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
// TODO: протестировать функции на предмет корректности

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;
using std::map;
using std::iterator;

using std::queue;

vector<vector<int>> readMatrix(string filename, bool isOriented = false); // чтение матрицы
map<int, vector<int>> readList(string filename, bool isOriented = false); // чтение списка (формат [1..n])

void showList(map<int, vector<int>>); // отображение списка
void showMatrix(vector<vector<int>>); // отображение матрицы

vector<vector<int>> makeRelMatrix(map<int, vector<int>>); // построение матрицы инциндентности
vector<vector<int>> makeRelMatrix(vector<vector<int>>); // -//-

bool listWidth(int, map<int, vector<int>>); // обход списка в ширину
bool matrixWidth(int, vector<vector<int>>); // обход матрицы в ширину

bool listDepth(int, map<int, vector<int>>); // обход списка в глубину
bool matrixDepth(int, vector<vector<int>>); // обход матрицы в глубину

int main(int argC, char** argV)
{
	int mode;
	cout << "Choose mode:" << endl << "1.Matrix" << endl << "2.List" << endl;
	cin >> mode;
	switch (mode)
	{
	case 1: // Matrix
	{
		int n = 0;
		vector<vector<int>> matrix = readMatrix("matrix.txt");
		showMatrix(matrix);
		cout << "Enter num between 1 and " << matrix.size() << " : ";
		cin >> n;
		if (n < 1 || n > matrix.size())
		{
			cout << "Wring parameter. Switched to 1." << endl;
			n = 1;
		}
		cout << "BFS" << endl;
		matrixWidth(n, matrix);
		cout << "DFS" << endl;
		matrixDepth(n, matrix);
	}
		break;
	case 2: // List
	{
		int n = 0;
		map<int, vector<int>> list = readList("list.txt");
		showList(list);
		cout << "Enter num between 1 and " << list.size() << " : ";
		cin >> n;
		if (n < 1 || n > list.size())
		{
			cout << "Wring parameter. Switched to 1." << endl;
			n = 1;
		}
		cout << "BFS" << endl;
		listWidth(n, list);
		cout << "DFS" << endl;
		listDepth(n, list);
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
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			result[i][j] = !isOriented ? abs(buf[i*n + j]) : buf[i*n + j];
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
	
	for (map<int, vector<int>>::iterator i = list.begin(); i != list.end(); i++)
	{
		cout << (*i).first + 1 << " : ";
		for (int j = 0; j < (*i).second.size(); j++)
		{
			cout << (*i).second[j] + 1 << " ";
		}
		cout << endl;
	}
}

void showMatrix(vector<vector<int>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
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
			if ((*it).second[i] > 0)
				relMatrix[(*it).first][(*it).second[i]] = 1;
			else if ((*it).second[i] > 0)
				relMatrix[(*it).first][(*it).second[i]] = -1;
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
			}
			else if (Buf[i][j] < 0)
			{
				Buf[i][j] = -1;
			}
		}
	}
	return Buf;
}

bool listDFS(int n, map<int, vector<int>> list, vector<bool> &used); // для рекурсии со списком
bool matrixDFS(int n, vector<vector<int>> matrix, vector<bool> &used);

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

	listDFS(n, list, used);

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

	matrixDFS(n, matrix, used);

	std::cout << std::endl;

	return false;
}

bool listDFS(int n, map<int, vector<int>> list, vector<bool> &used)
{
	std::cout << n + 1 << " ";

	used[n] = true;

	vector<int> searched = list[n];

	for (int i = 0; i < searched.size(); i++)
	{
		if (!used[searched[i]])
			listDFS(searched[i], list, used);
	}

	return false;
}

bool matrixDFS(int n, vector<vector<int>> matrix, vector<bool>& used)
{
	std::cout << n + 1 << " ";

	used[n] = true;
	vector<int> searched = matrix[n];
	for (int i = 0; i < searched.size(); i++)
	{
		if (!used[i])
		{
			matrixDFS(i, matrix, used);
		}
	}

	return false;
}
