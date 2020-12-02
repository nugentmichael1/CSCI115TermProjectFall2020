#pragma once


//random number generator
void fillArr(vector<int>& arr, int range);
void fillArr(int arr[], int size, int range);

//print array
void prntArr(vector<int>& arr);

//output formatting.  prints out title of respective case chosen.
void header(int inptCse);
//output formatting.  prints range used.
void rangeFormat(int uC, int bestRange, int avgRange);


void rangeFormat(int uC, int bestRange, int avgRange) {
	cout << "Range: ";
	if (uC == 1) cout << bestRange;
	else if (uC == 2)cout << avgRange;
	else cout << INT_MAX / 1000;
	cout << "\n";
}

void header(int inptCse) {
	cout << "Batch\t";
	if (inptCse == 1)cout << "Best-Case\n";
	else if (inptCse == 2) cout << "Average-Case\n";
	else if (inptCse == 3) cout << "Worst-Case\n";
}

void fillArr(vector<int>& arr, int range) {
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = rand() % range;
	}
}

void fillArr(int arr[], int size, int range) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % range;
	}
}

void prntArr(vector<int>& arr) {
	for (auto a : arr) cout << a << " ";
	cout << "\n";
}
