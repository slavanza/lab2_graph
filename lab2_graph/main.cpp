#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <iterator>

// TODO: �������� ������� ������ �����


using std::string;
using std::vector;
using std::map;
using std::iterator;

vector<vector<int>> readMatrix(string filename); // ������ �������
map<int, vector<int>> readList(string filename); // ������ ������

void showList(map<int, vector<int>>); // ����������� ������
void showMatrix(vector<vector<int>>); // ����������� �������

vector<vector<int>> makeRelMatrix(map<int, vector<int>>); // ���������� ������� ��������������
vector<vector<int>> makeRelMatrix(vector<vector<int>>); // -//-

bool listWidth(int, map<int, vector<int>>); // ����� ������ � ������
bool matrixWidth(int, vector<vector<int>>); // ����� ������� � ������

bool listDepth(int, map<int, vector<int>>); // ����� ������ � �������
bool matrixDepth(int, vector<vector<int>>); // ����� ������� � �������

int main(int argC, char** argV)
{
	vector<vector<int>> matrix = readMatrix("matrix.txt");
	map<int, vector<int>> list = readList("list.txt");

	showMatrix(matrix);
	showList(list);

	makeRelMatrix(matrix);
	makeRelMatrix(list);



	// TODO: ��������� main

	// ������ +
	// ����� +
	// ������� ������� +
	// ����� -


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

	// TODO: ������� ���������� �������
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

bool listWidth(int, map<int, vector<int>>) // ����� ������ � ������
{
	return false;
}

bool listDepth(int, map<int, vector<int>>) // ����� ������ � �������
{
	return false;
}

bool matrixWidth(int, vector<vector<int>>) // ����� ������� � ������
{
	return false;
}

bool matrixDepth(int, vector<vector<int>>) // ����� ������� � ������� 
{
	return false;
}
