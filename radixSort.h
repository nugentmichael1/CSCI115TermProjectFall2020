#pragma once
#include<iostream>
#include<vector>
#include<chrono>
#include<math.h>
using namespace std;
using namespace std::chrono;

void print(vector<int>* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << a->at(i) << " ";
	}
	cout << endl;
}

void countingSortRad(vector<int>* a, int size, int ex)
{
	vector<int> aux;
	vector<int>output;

	for (int i = 0; i < 10; i++)
	{
		aux.push_back(0);
	}

	for (int j = 0; j < size; j++) // set index
	{
		aux.at((a->at(j) / ex) % 10)++;
		output.push_back(0);
	}

	for (int k = 1; k < 10; k++) // sum
	{
		aux.at(k) += aux.at(k - 1);
	}

	for (int l = size - 1; l >= 0; l--) // setting up output
	{
		output.at(aux.at((a->at(l) / ex) % 10) - 1) = a->at(l);
		aux.at((a->at(l) / ex) % 10)--;
	}

	for (int m = 0; m < size; m++) // set new values
	{
		a->at(m) = output.at(m);
	}
}

void RadixSort(vector<int>* a, int size, int max)
{
	int digits = 0;
	/*while (max != 0)
	{
		digits++;
		max /= 10;
	}*/

	for (int i = 1; max / i > 0; i *= 10)
	{
		countingSortRad(a, size, i);
	}
}

/*
int main()
{
	vector<int> a;

	for (int i = 0; i < 100000; i++) // n size
	{
		a.push_back(rand() % 32000); // 5 digits. ~32000 is max number for rand()
	}

	int max = 0;

	for (int s = 0; s < a.size() - 1; s++)
	{
		if (max < a.at(s))
		{
			max = a.at(s);
		}
	}

	auto start1 = high_resolution_clock::now();
	RadixSort(&a, a.size(), max);
	auto stop1 = high_resolution_clock::now();

	print(&a, a.size());

	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	cout << "Time in microseconds " << (float)duration1.count() << endl;

}
*/