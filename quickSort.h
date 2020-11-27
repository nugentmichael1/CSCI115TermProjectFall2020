#pragma once
#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;



///
///AUXILIARY FUNCTIONS
///

/*
void printArray(int A[], int size) {
	for (int i = 0; i < size - 1; i++) {
		cout << A[i] << ", ";
	}
	cout << A[size - 1] << endl;
}
*/

void swap(int A[], int l, int r) {
	int temp = A[l];
	A[l] = A[r];
	A[r] = temp;
}

int median(int first, int mid, int last) {
	int median = last;
	int min = last;
	int max = last;

	if (first < mid) {
		min = first;
		max = mid;
	}
	else {
		min = mid;
		max = first;
	}

	if (median > max) {
		int temp = median;
		median = max;
		max = temp;
	}
	if (median < min) {
		int temp = median;
		median = min;
		min = temp;
	}

	return median;
}

int getRand(int p, int r) {
	int size = r - p + 1;
	int random = rand() % size;
	return random + p;
}

int generateRand() {
	int random = rand() % 200;
	random = random % rand();
	return random;
}

///
///PIVOT IS ALWAYS A[R]
///
int partition(int A[], int p, int r) {
	int x = A[r];
	int i = p - 1;

	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			++i;
			swap(A, i, j);
		}
	}

	swap(A, i + 1, r);

	return i + 1;
}

int partitionFirst(int A[], int p, int r) {
	swap(A, p, r);
	return partition(A, p, r);
}

int partitionRandom(int A[], int p, int r) {
	int random = getRand(p, r);
	swap(A, random, r);
	return partition(A, p, r);
}

int partitionMedian(int A[], int p, int r) {
	int mid = p + (r - p) / 2;
	int med = median(p, mid, r);
	swap(A, med, r);
	return partition(A, p, r);
}


void quick_sort(int A[], int p, int r, int input) {
	if (p < r) {
		int q;
		if (input == 1) {
			q = partitionFirst(A, p, r);
		}
		else if (input == 2) {
			q = partitionRandom(A, p, r);
		}
		else if (input == 3) {
			q = partitionMedian(A, p, r);
		}
		else {
			return;
		}
		quick_sort(A, p, q - 1, input);
		quick_sort(A, q + 1, r, input);
	}
}

/*
int main() {

	using namespace std::chrono;

	steady_clock::time_point t1, t2;
	duration<double> time_span_best, time_span_worst, time_span_average;

	int input;
	int best[1000];		//unsorted distinct elements
	int worst[1000];	//sorted elements
	int average[1000];  //unsorted with possible duplicate elements


	for (int i = 0; i < 1000; i++) {
		average[i] = generateRand();
		best[i] = i;
		worst[i] = i;
	}

	for (int i = 0; i < 1000; i++) {
		int random = getRand(i, 1000);
		swap(best, i, random);
	}


	quick_sort(worst, 0, 999, 1);


	cout << "Enter an option for pivot:\n";
	cout << "1) First element.\n2) Random element.\n3) Median of first, middle, and last element.\n";
	cin >> input;

	t1 = steady_clock::now();
	quick_sort(best, 0, 999, input);
	t2 = steady_clock::now();
	time_span_best = duration_cast<duration<double>>(t2 - t1);

	t1 = steady_clock::now();
	quick_sort(worst, 0, 999, input);
	t2 = steady_clock::now();
	time_span_worst = duration_cast<duration<double>>(t2 - t1);

	t1 = steady_clock::now();
	quick_sort(average, 0, 999, input);
	t2 = steady_clock::now();
	time_span_average = duration_cast<duration<double>>(t2 - t1);

	cout << "Best-case Input: " << time_span_best.count() << " seconds.\n";
	cout << "Worst-case Input: " << time_span_worst.count() << " seconds.\n";
	cout << "Average-case Input: " << time_span_average.count() << " seconds.\n";

	return 0;
}

*/