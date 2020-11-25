#pragma once

#include <vector>;

using namespace std;

void selectionSort(vector<int>& arr);

void selectionSort(vector<int>& arr) {
	for (int i = 0; i < arr.size() - 1; i++) {
		int min = i;
		//find smallest element
		for (int j = i+1; j < arr.size(); j++) {
			if (arr[min] > arr[j]) min = j;
		}
		//swap smallest element of unsorted range with element at i
		int tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
	}
}
