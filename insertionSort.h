#pragma once

#include <vector>;
#include <time.h>;

using namespace std;

int insertionSort(vector<int>& arr);

int insertionSort(vector<int>& arr) {
	int comparisons = 0;
	for (int j = 1; j < arr.size(); j++) {
		int key = arr[j];
		int i = j - 1;
		comparisons++;
		while (i >= 0 && key < arr[i]) {
			arr[i + 1] = arr[i];
			i--;
			comparisons++;
		}
		arr[i + 1] = key;
	}
	return comparisons;
}