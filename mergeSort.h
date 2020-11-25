#pragma once
// C++ program to generate Worst Case
// of Merge Sort
#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

void merge(int *arr, int low, int mid, int high);

void mergeSort(int *arr, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);

		// This is where we optimize for best
		// case.
		if (arr[mid] > arr[mid + 1])
			merge(arr, low, mid, high);
	}
}

void merge(int *arr, int low, int mid, int high)
{
	int i = low, j = mid + 1, k = 0;
	int *temp = (int *)calloc(high - low + 1, sizeof(int));
	while ((i <= mid) && (j <= high))
		if (arr[i] < arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	while (j <= high) // if( i>mid )
		temp[k++] = arr[j++];
	while (i <= mid) // j>high
		temp[k++] = arr[i++];

	// copy temp[] to arr[]
	for (i = low, k = 0; i <= high; i++, k++)
		arr[i] = temp[k];
	free(temp);
}
// Function to print an array
void printArray(int A[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

// Function to join left and right subarray
int join(int arr[], int left[], int right[],
		 int l, int m, int r)
{
	int i;
	for (i = 0; i <= m - l; i++)
		arr[i] = left[i];

	for (int j = 0; j < r - m; j++)
	{
		arr[i + j] = right[j];
	}
	return 1;
}

// Function to store alternate elemets in
// left and right subarray
int split(int arr[], int left[], int right[],
		  int l, int m, int r)
{
	for (int i = 0; i <= m - l; i++)
		left[i] = arr[i * 2];

	for (int i = 0; i < r - m; i++)
		right[i] = arr[i * 2 + 1];
	return 1;
}

// Function to generate Worst Case
// of Merge Sort
int generateWorstCase(int arr[], int l,
					  int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;

		// Create two auxiliary arrays
		//int left[m - l + 1];
		//int right[r - m];
		int* left = new int[m - l + 1];
		int* right = new int[r - m];

		// Store alternate array elements
		// in left and right subarray
		split(arr, left, right, l, m, r);

		// Recurse first and second halves
		generateWorstCase(left, l, m);
		generateWorstCase(right, m + 1, r);

		// Join left and right subarray
		join(arr, left, right, l, m, r);
	}
	return 1;
}

/*
// Driver code
int main()
{
	clock_t start, end;
	start = clock();
	// Sorted array

	int x = 1000;
	int y = 10000;
	int z = 100000;
	//int arr[x]; //changed to line beneath.  mjn
	int* arr = new int[x];
	for (int i = 1; i <= x; i++)
	{
		arr[i - 1] = i;
	}

	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "Sorted array is \n";
	printArray(arr, n);

	// Generate Worst Case of Merge Sort
	generateWorstCase(arr, 0, n - 1);

	cout << "\nInput array that will result "
		 << "in worst case of merge sort is \n";
	printArray(arr, n);
	cout << endl;
	mergeSort(arr, 0, x - 1);
	cout << "After merge sort the sorted array is: " << endl;
	printArray(arr, n);

	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken by program is : " << fixed
		 << time_taken << setprecision(5);
	cout << " sec " << endl;
	return 0;
}
*/