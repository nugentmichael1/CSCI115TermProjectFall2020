#pragma once

#include <vector>;
#include <time.h>;

using namespace std;

void insertionSort(vector<int>& arr);

void insertionSort(vector<int>& arr) {
	for (int j = 1; j < arr.size(); j++) {
		int key = arr[j];
		int i = j - 1;
		while (i >= 0 && key < arr[i]) {
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i + 1] = key;
	}
}