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

// TODO: реализовать функции обхода графа


using std::string;
using std::vector;
using std::map;
using std::iterator;

using std::queue;

vector<vector<int>> readMatrix(string filename); // чтение матрицы
map<int, vector<int>> readList(string filename); // чтение списка

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
	vector<vector<int>> matrix = readMatrix("matrix.txt");
	map<int, vector<int>> list = readList("list.txt");

	showMatrix(matrix);
	showList(list);

	makeRelMatrix(matrix);
	makeRelMatrix(list);



	// TODO: заполнить main

	// чтение +
	// вывод +
	// рассчёт матрицы +
	// обход +
	// вывод обхода на экран -


	return 0;
}

vector<vector<int>> readMatrix(string filename)
{
	std::ifstream file;
	file.open(filename);
	vector<int> buf;
	while (!file.eof())
	{
		buf.push_back(file.get());
	}
	vector<vector<int>> result(sqrt(buf.size()));
	for (int i = 0; i < sqrt(buf.size()); i++)
	{
		for (int j = 0; j < sqrt(buf.size()); j++)
		{
			result[i][j] = buf[i*sqrt(buf.size()) + j];
		}
	}
	file.close();
	return result;
}

map<int, vector<int>> readList(string filename)
{
	std::ifstream file;
	file.open(filename);
	int _buf1, _buf2;
	map<int, vector<int>> result;
	while (!file.eof())
	{
		_buf1 = file.get();
		_buf2 = file.get();

		result[_buf1].push_back(_buf2);
	}
	return result;
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
	if (n < 0 || n > list.size())
		throw std::exception("bad argument");
	queue<int> q;
	vector<bool> used(list.size());
	q.push(n);
	while(!q.empty())
	{
		int v = q.front();

		std::cout << v << " ";

		used[v] = true;
		q.pop();
		for (int i = 0; i < list[v].size(); i++)
		{
			if(!used[list[v][i]])
				q.push(list[v][i]);
		}
	}

	std::cout << std::endl;

	return false;
}

bool listDepth(int n, map<int, vector<int>> list) // обход списка в глубину
{
	if (n < 0 || n > list.size())
		throw std::exception("bad argument");

	vector<bool> used(list.size());

	listDFS(n, list, used);

	std::cout << std::endl;

	return false;
}

bool matrixWidth(int n, vector<vector<int>> matrix) // обход матрицы в ширину
{
	if (n < 0 || n > matrix[0].size())
		throw std::exception("bad argument");
	queue<int> q;
	vector<bool> used(matrix[0].size());
	q.push(n);
	while (!q.empty())
	{
		int v = q.front();

		std::cout << v << " ";

		used[v] = true;
		q.pop();
		for (int i = 0; i < matrix[v].size(); i++)
		{
			if (matrix[v][i] && !used[matrix[v][i]])
				q.push(matrix[v][i]);
		}
	}

	std::cout << std::endl;

	return false;
}

bool matrixDepth(int n, vector<vector<int>> matrix) // обход матрицы в глубину 
{
	if (n < 0 || n > matrix[0].size())
		throw std::exception("bad argument");
	vector<bool> used(matrix[0].size());

	matrixDFS(n, matrix, used);

	std::cout << std::endl;

	return false;
}


bool listDFS(int n, map<int, vector<int>> list, vector<bool> &used)
{
	std::cout << n << " ";

	used[n] = true;

	vector<int> searched = list[n];

	for (int i = 0; i < searched.size(); i++)
	{
		if (!used[searched[i]])
			listDFS(searched[i], list, used);
	}
}

bool matrixDFS(int n, vector<vector<int>> matrix, vector<bool>& used)
{
	std::cout << n << " ";

	used[n] = true;
	vector<int> searched = matrix[n];

	for (int i = 0; i < searched.size(); i++)
	{
		if (!used[searched[i]])
			matrixDFS(searched[i], matrix, used);
	}

	return false;
}
