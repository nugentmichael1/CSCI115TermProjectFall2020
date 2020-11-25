/*
* CSCI 115 - Term Project: Theory vs Performance of Sort Algorithms
*
* Team Members: Emmanuel Cardenas, Ashley Taylor Diaz, Narendra Mannan, Michael Nugent, and Kalvin Xiong
*/

//public libraries
#include <vector> //array container
#include "time.h" //seed random number generator
#include <chrono> //measure function execution times
#include <iostream> //output to display


//student libraries
#include "insertionSort.h" //insertion sort algorithm functions
#include "selectionSort.h" //selection sort
#include "bubbleSort.h" //bubble Sort
#include "mergeSort.h" //merge sort
#include "heapSort.h" //heapSort
#include "countingSort.h"//countingSort
#include "radixSort.h"


using namespace std;


//random number generator
void fillArr(vector<int>& arr, int range);
void fillArr(int arr[], int size, int range);

//print array
void prntArr(vector<int>& arr);

//output formatting.  prints out title of respective case chosen.
void header(int inptCse);
//output formatting.  prints range used.
void rangeFormat(int uC, int bestRange, int avgRange);


//functions to test respective sorting algorithms and store execution times
void insertionSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration);
void selectionSortTest(vector<vector<int>>& batch, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
void bubbleSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
void mergeSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
void quickSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
void heapSortTest(vector<vector<int>>& batch, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
int countingSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
int radixSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);


int main() {

	//initializations
	int size = 0,
		range = 10000;
	int batches = 0;
	int sorts = 1;
	int sizeCases = 0;
	int inputCases = 1;
	int bestRange = 0;//holds range value calculated by non-comparison sorts (counting & radix) for best input-case

	//user input variables
	int userChoice[4]{ 0,0,0,0 };

	//Display Program Title
	cout << "CSCI 115 - Term Project: Comparison of Sorting Algorithms\n\n";

	//Inform user of sorting algorithm options and query for decision.
	while (userChoice[0] < 1 || userChoice[0]>9) {
		cout << "Please choose a sorting algorithm.\n";
		cout << "(1) - Insertion\n";
		cout << "(2) - Selection\n";
		cout << "(3) - Bubble\n";
		cout << "(4) - Merge\n";
		cout << "(5) - Quick\n";
		cout << "(6) - Heap\n";
		cout << "(7) - Counting\n";
		cout << "(8) - Radix\n";
		cout << "(9) - Do All\n";

		cin >> userChoice[0];
	}

	//define number of sorting algorithms to test.  will be 1 or 8.
	if (userChoice[0] == 9)sorts = 8;

	//Query user for input-case: best, average, and/or worst.
	if (userChoice[0] == 1 || //insertion
		userChoice[0] == 3 || //bubble
		userChoice[0] == 4 || //merge
		userChoice[0] == 5 || //quick
		userChoice[0] == 7 || //counting
		userChoice[0] == 8 || //radix

		userChoice[0] == 9 //all
		) {
		userChoice[1] = 0;
		while (userChoice[1] < 1 || userChoice[1]>4) {
			cout << "Please choose an input-case type:\n";
			cout << "(1) Best\n";
			cout << "(2) Average\n";
			cout << "(3) Worst\n";
			cout << "(4) Do All\n";
			cin >> userChoice[1];
		}
	}
	//define cases count for "Do All" selection
	if (userChoice[1] == 4)inputCases = 3;

	//Inform user of input size options and query for decision.
	while (userChoice[2] < 1) {
		cout << "Please choose an input size:\n";
		cout << "(1) - 1,000\n";
		cout << "(2) - 10,000\n";
		cout << "(3) - 100,000\n";
		//cout << "(4) - Do All\n"; //too cumbersome to include "Do all"
		cout << "Or manually input a size.\n";

		cin >> userChoice[2];
	}

	//update size variable based on user input
	if (userChoice[2] == 1)size = 1000;
	else if (userChoice[2] == 2)size = 10000;
	else if (userChoice[2] == 3)size = 100000;
	//else if (userChoice[2] == 4)sizeCases = 3; //too cumbersome to include "Do all"
	else size = userChoice[2];

	//acquire batches needed from user
	while (userChoice[3] < 1) {
		//Inform user of options and query for decision.
		cout << "Please input number of batches:\n";
		cin >> userChoice[3];
		//cout << userChoice[3] << " batches";
	}

	batches = userChoice[3];

	//for comparison sorts
	vector<vector<int>> batch(batches, //# of batches.  user-defined.
		vector<int>(size));//size
	//non-comparison sorts
	vector<vector<int>> batchNonCmpr(batches, //#of batches. user-defined
		vector<int>(size));//size

	//3d vector of microseconds to store execution-times of each sort call per batch per input-case
	vector<vector<vector<chrono::microseconds>>> duration(sorts, //sorting algorithm(s).  will be 1 or 8.
		vector<vector<chrono::microseconds>>(inputCases, //# of input case types.  will be 1 or 3: best, average, worst.
			vector<chrono::microseconds>(batches)));//# of batches: user defined.

	//generate random arrays
	srand(time(NULL)); //seed random number generator
	for (int i = 0; i < batch.size(); i++) fillArr(batch[i], range);

	//Display "Execution times" header prior to algorithm if-tree.
	//display algorithm name in each if statement
	cout << "\n\n -- Execution times (microseconds) -- \n";

	//individual sorting algorithms
	if (userChoice[0] == 1) { //insertion
		cout << "Insertion Sort\n";
		insertionSortTest(batch, userChoice[1], duration);
	}

	else if (userChoice[0] == 2) {//selection
		cout << "Selection Sort\n";
		selectionSortTest(batch, duration, false);//no input-case argument because all input-cases are equal
	}

	else if (userChoice[0] == 3) {//bubble
		cout << "Bubble Sort\n";
		bubbleSortTest(batch, userChoice[1], duration, false);
	}

	else if (userChoice[0] == 4) {//merge
		cout << "Merge Sort\n";
		mergeSortTest(batch, userChoice[1], duration, false);
	}
	else if (userChoice[0] == 5) {//quick
		cout << "Quick Sort\n";

		/*
		//may automatically include this in case decision
		if (userChoice[0] == 5) {
			cout << "Please choose a pivot type for quicksort.";
			cout << "(1) First element\n";
			cout << "(2) Random element\n";
			cout << "(3) Median of first, middle, and last element\n";
			cin >> quickPivot;
		}
		*/
	}
	else if (userChoice[0] == 6) {//heap
		cout << "Heap Sort\n";
		heapSortTest(batch, duration, false);
	}
	else if (userChoice[0] == 7) {//counting
		cout << "Counting Sort\n";
		bestRange = countingSortTest(batch, userChoice[1], duration, false);
	}
	else if (userChoice[0] == 8) {//radix
		cout << "Radix Sort\n";
		bestRange = radixSortTest(batch, userChoice[1], duration, false);
	}

	//all sorting algorithms
	else { //9: do all
	//feed sorting algorithm tests copies of batches so as to preserve originals

		//insertionSort
		//make temporary copy of input array to preserve original.
		vector<vector<int>> tmp(batch);
		insertionSortTest(tmp, userChoice[1], duration);

		//selectionSort
		//make copy of batch
		tmp.assign(batch.begin(), batch.end());
		selectionSortTest(tmp, duration, true);

		//bubbleSort
		//refresh batch copy in tmp
		tmp.assign(batch.begin(), batch.end());
		bubbleSortTest(tmp, userChoice[1], duration, true);

		//mergeSort
		tmp.assign(batch.begin(), batch.end());
		mergeSortTest(tmp, userChoice[1], duration, true);

		//quickSort
			//each input case should use a most appropriate pivot?

		//heapSort
		tmp.assign(batch.begin(), batch.end());
		heapSortTest(tmp, duration, true);

		//countingSort
		bestRange = countingSortTest(batch, userChoice[1], duration, true);

		//radixSort
		radixSortTest(batch, userChoice[1], duration, true);
	}


	//send data to display.

	//all 8 algorithms selected
	if (userChoice[0] == 9) {
		//all input-cases: best, average, worst
		if (userChoice[1] == 4) {
			//insertion
			cout << "\nInsertion Sort\n";
			cout << "Batch\tBest-Case\tAverage-Case\tWorst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[0][0][i].count() << "\t\t" << duration[0][1][i].count() << "\t\t" << duration[0][2][i].count() << "\n";
			}
			//selection
			cout << "\nSelection Sort\n";
			cout << "Batch\tBest-Case = Average-Case = Worst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t\t\t" << duration[1][0][i].count() << "\n";
			}
			//bubble
			cout << "\nBubble Sort\n";
			cout << "Batch\tBest-Case\tAverage-Case\tWorst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[2][0][i].count() << "\t\t" << duration[2][1][i].count() << "\t\t" << duration[2][2][i].count() << "\n";
			}
			//merge
			cout << "\nMerge Sort\n";
			cout << "Batch\tBest-Case\tAverage-Case\tWorst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[3][0][i].count() << "\t\t" << duration[3][1][i].count() << "\t\t" << duration[3][2][i].count() << "\n";
			}
			//quick
			cout << "\nQuick Sort\n";
			cout << "Batch\tBest-Case\tAverage-Case\tWorst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[4][0][i].count() << "\t\t" << duration[4][1][i].count() << "\t\t" << duration[4][2][i].count() << "\n";
			}
			//heap
			cout << "\nHeap Sort\n";
			cout << "Batch\tBest-Case = Average-Case = Worst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t\t\t" << duration[5][0][i].count() << "\n";
			}
			//counting
			cout << "\nCounting Sort\n";
			cout << "Batch\tBest-Case\tAverage-Case\tWorst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[6][0][i].count() << "\t\t" << duration[6][1][i].count() << "\t\t" << duration[6][2][i].count() << "\n";
			}
			cout << "\nRange\t[0, " << bestRange << ")\t[0, " << batch[0].size() << ")\t[0," << INT_MAX / 1000 << ")\n\n";

			//radix
			cout << "\nRadix Sort\n";
			cout << "Batch\tBest-Case\tAverage-Case\tWorst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[7][0][i].count() << "\t\t" << duration[7][1][i].count() << "\t\t" << duration[7][2][i].count() << "\n";
			}
			cout << "\nRange\t[0, " << bestRange << ")\t[0, " << batch[0].size() << ")\t[0," << INT_MAX / 1000 << ")\n\n";

		}
		//one input-case
		else {
			//insertion
			cout << "\nInsertion Sort\n";
			header(userChoice[1]);
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[0][0][i].count() << "\n";
			}
			//selection
			cout << "\nSelection Sort\n";
			cout << "Batch\tBest-Case = Average-Case = Worst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t\t\t" << duration[1][0][i].count() << "\n";
			}
			//bubble
			cout << "\nBubble Sort\n";
			header(userChoice[1]);
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[2][0][i].count() << "\n";
			}
			//merge
			cout << "\nMerge Sort\n";
			header(userChoice[1]);
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[3][0][i].count() << "\n";
			}
			//quick
			cout << "\nQuick Sort\n";
			header(userChoice[1]);
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[4][0][i].count() << "\n";
			}
			//heap
			cout << "\nHeap Sort\n";
			cout << "Batch\tBest-Case = Average-Case = Worst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t\t\t" << duration[5][0][i].count() << "\n";
			}

			//counting
			cout << "\nCounting Sort\n";
			header(userChoice[1]);
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[6][0][i].count() << "\n";
			}
			rangeFormat(userChoice[1], bestRange, batch[0].size());


			//radix
			cout << "\nRadix Sort\n";
			header(userChoice[1]);
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[7][0][i].count() << "\n";
			}
			rangeFormat(userChoice[1], bestRange, batch[0].size());

		}
	}
	//only 1 algorithm selected
	else {
		//all 3 input case types: best, average, worst
		if (userChoice[1] == 4) {
			cout << "\t\tAll Input-Cases\n";
			cout << "Batch\tBest-Case\tAverage-Case\tWorst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[0][0][i].count() << "\t\t" << duration[0][1][i].count() << "\t\t" << duration[0][2][i].count() << "\n";
			}
			if (userChoice[0] == 7 || userChoice[0] == 8) cout << "\nRange\t[0, " << bestRange << ")\t[0, " << batch[0].size() << ")\t[0," << INT_MAX / 1000 << ")\n\n";
		}
		//only selection or heap (XOR)
		else if (userChoice[1] == 0) {
			cout << "Batch\tBest-Case = Average-Case = Worst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t\t\t" << duration[0][0][i].count() << "\n";
			}

		}
		//only 1 input-case.  not selection or heap
		else {
			header(userChoice[1]);
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[0][0][i].count() << "\n";
			}
			if (userChoice[0] == 7 || userChoice[0] == 8) rangeFormat(userChoice[1], bestRange, batch[0].size());

		}
		cout << "\nn = " << size << "\n";
	}
}

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

void insertionSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	if (inputCase == 1) {//best case input
		for (int i = 0; i < batch.size(); i++) {

			//make temporary copy of input array to preserve original.
			vector<int> tmp(batch[i]);

			//sort tmp array to create best insertion case input
			insertionSort(tmp);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			insertionSort(tmp);

			stop = chrono::high_resolution_clock::now();

			duration[0][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
	else if (inputCase == 2) //average case input
	{
		for (int i = 0; i < batch.size(); i++) {

			//make temporary copy of input array to preserve original.
			vector<int> tmp(batch[i]);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			insertionSort(tmp);

			stop = chrono::high_resolution_clock::now();

			duration[0][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
	else if (inputCase == 3) { //worst case input
		for (int i = 0; i < batch.size(); i++) {
			//make temporary copy of input array to preserve original.
			vector<int> tmp(batch[i]);

			//sort tmp array to create best insertion case input
			insertionSort(tmp);
			//reverse sort sorted tmp array to creat worst case input
			reverse(tmp.begin(), tmp.end());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			insertionSort(tmp);

			stop = chrono::high_resolution_clock::now();

			duration[0][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
	else {//inputCase==4. do all
		//average, best, worst
		for (int i = 0; i < batch.size(); i++) {
			//make temporary copy of input array to preserve original.
			vector<int> tmp(batch[i]);

			//average case: random distribution
			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			insertionSort(tmp);

			stop = chrono::high_resolution_clock::now();

			duration[0][1][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

			//best case: already sorted
			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			insertionSort(tmp);

			stop = chrono::high_resolution_clock::now();

			duration[0][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

			//worst case: reverse sorted
			reverse(tmp.begin(), tmp.end());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			insertionSort(tmp);

			stop = chrono::high_resolution_clock::now();

			duration[0][2][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
}

void selectionSortTest(vector<vector<int>>& batch, vector<vector<vector<chrono::microseconds>>>& duration, bool multi) {

	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	for (int i = 0; i < batch.size(); i++) {
		//all input cases are equal

		//start stopwatch
		start = chrono::high_resolution_clock::now();

		//sort
		insertionSort(batch[i]);

		//stop stopwatch
		stop = chrono::high_resolution_clock::now();

		//if bool value "multi" is true send data to duration[1], otherwise duration[0].
		duration[multi ? 1 : 0][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
	}
}

void bubbleSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi) {

	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	int algoPos = (multi) ? 2 : 0; //if all algorithms are tested data must be sent to vector position [2] of duration, else [0]

	if (inputCase == 1) {//best case input
		for (int i = 0; i < batch.size(); i++) {

			//copy vector array to int array to comply with bubbleSort parameters
			int* tmp = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) tmp[j] = batch[i][j];

			//debug
			//cout << "\nPrinting initial array provided to best-case of Bubble Sort\n";
			//printArray(tmp, batch[i].size());

			//sort tmp array to create best BubbleSort input-case
			bubbleSort(tmp, batch[i].size());

			//debug
			//cout << "Printing sorted array of Bubble Sort\n";
			//printArray(tmp, batch[i].size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			bubbleSort(tmp, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

			//debug
			//cout << "Printing result of best-case input of Bubble Sort\n";
			//printArray(tmp, batch[i].size());

		}
	}
	else if (inputCase == 2) //average case input
	{
		for (int i = 0; i < batch.size(); i++) {

			//copy vector array to int array to comply with bubbleSort parameters
			int* tmp = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) tmp[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			bubbleSort(tmp, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
	else if (inputCase == 3) { //worst case input
		for (int i = 0; i < batch.size(); i++) {

			//copy vector array to int array to comply with bubbleSort parameters
			int* tmp = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) tmp[j] = batch[i][j];

			//sort tmp array to prepare worst-case input of bubbleSort
			bubbleSort(tmp, batch[i].size());
			//reverse sorted tmp array to create worst-case bubbleSort input
			for (int j = 0, k = batch[i].size() - 1; j < k; j++, k--) {
				int swapTmp = tmp[j];
				tmp[j] = tmp[k];
				tmp[k] = swapTmp;
			}

			//debug
			//cout << "\nReverse Sorted Array -- worst-case bubble sort input\n";
			//printArray(tmp, batch[i].size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			bubbleSort(tmp, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
	else {//userChoice[1]==4. do all
		//average, best, worst
		for (int i = 0; i < batch.size(); i++) {
			//(1)average case: random distribution
			//copy vector array to int array to comply with bubbleSort parameters
			int* tmp = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) tmp[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			bubbleSort(tmp, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][1][i] = chrono::duration_cast<chrono::microseconds>(stop - start);


			//best case: already sorted
			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			bubbleSort(tmp, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);


			//worst case: reverse sorted
			//reverse sorted tmp array to create worst-case bubbleSort input
			for (int j = 0, k = batch[i].size() - 1; j < k; j++, k--) {
				int swapTmp = tmp[j];
				tmp[j] = tmp[k];
				tmp[k] = swapTmp;
			}

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			bubbleSort(tmp, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][2][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
}

void mergeSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	int algoPos = (multi) ? 3 : 0; //if all algorithms are tested, data must be sent to vector position [3] of duration, else [0]

	if (inputCase == 1) {//best case input
		for (int i = 0; i < batch.size(); i++) {

			//copy vector array to int array to comply with mergeSort parameters
			int* tmp = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) tmp[j] = batch[i][j];

			//sort tmp array to create best mergeSort case input
			mergeSort(tmp, 0, batch[i].size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			mergeSort(tmp, 0, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

			//debug
			//cout << "Printing result of mergeSort\n";
			//printArray(tmp, batch[i].size());
		}
	}
	else if (inputCase == 2) //average case input
	{
		for (int i = 0; i < batch.size(); i++) {

			//copy vector array to temporary int array to comply with mergeSort parameters
			int* tmp = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) {
				tmp[j] = batch[i][j];
			}

			//debug
			//cout << "\nPrinting initial array of mergeSort\n";
			//printArray(tmp, batch[i].size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			mergeSort(tmp, 0, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

			//debug
			//cout << "Printing result of mergeSort\n";
			//printArray(tmp, batch[i].size());
		}
	}
	else if (inputCase == 3) { //worst case input
		for (int i = 0; i < batch.size(); i++) {

			//copy vector array to temporary int array to comply with mergeSort parameters
			int* tmp = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) tmp[j] = batch[i][j];

			//sort array in preparation of worst case
			mergeSort(tmp, 0, batch[i].size());
			//recursively split sorted array to create worst case input
			generateWorstCase(tmp, 0, batch[i].size());

			//debug
			//cout << "Printing worst-case input\n";
			//printArray(tmp, batch[i].size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			mergeSort(tmp, 0, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

			//debug
			//cout << "Printing result of mergeSort\n";
			//printArray(tmp, batch[i].size());
		}
	}
	else {//userChoice[1]==4. do all
		//average, best, worst
		for (int i = 0; i < batch.size(); i++) {
			//copy vector array to int array to comply with mergeSort parameters
			int* tmp = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) tmp[j] = batch[i][j];


			//average case: random distribution
			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			mergeSort(tmp, 0, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][1][i] = chrono::duration_cast<chrono::microseconds>(stop - start);


			//best case: already sorted
			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			mergeSort(tmp, 0, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);


			//worst case: sorted recursively split
			//already sorted from previous operation
			generateWorstCase(tmp, 0, batch[i].size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			mergeSort(tmp, 0, batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][2][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
}

void quickSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	int algoPos = (multi) ? 4 : 0; //if all algorithms are tested, data must be sent to vector position [4] of duration, else [0]
}

void heapSortTest(vector<vector<int>>& batch, vector<vector<vector<chrono::microseconds>>>& duration, bool multi) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	int algoPos = (multi) ? 5 : 0; //if all algorithms are tested, data must be sent to vector position [5] of duration, else [0]

	//all input-cases result in identical outputs
	for (int i = 0; i < batch.size(); i++) {

		MaxHeap tmp;
		for (auto a : batch[i])tmp.Insert(a);


		//start stopwatch
		start = chrono::high_resolution_clock::now();

		//sort
		tmp.HeapSort();

		//stop stopwatch
		stop = chrono::high_resolution_clock::now();

		duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

		//debug
		//cout << "\nPrinting heapSort result\n";
		//tmp.printSortedArray();
	}
}

int countingSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	int algoPos = (multi) ? 6 : 0; //if all algorithms are tested, data must be sent to vector position [6] of duration, else [0]
	int inputCasePos = 0;
	int bestRange = (int)sqrt((double)batch[0].size());
	int worstRange = INT_MAX/1000;
	
	//int array to comply with CountingSort's parameters
	int* tmpArr = new int[batch[0].size()];


	if (inputCase == 1) {//best case input
		for (int i = 0; i < batch.size(); i++) {

			//best case requires low range.  fill vector with low range values.
			fillArr(tmpArr, batch[0].size(), bestRange);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			CountingSort(tmpArr, batch[i].size(), bestRange);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

		}
	}
	else if (inputCase == 2) //average case input
	{
		for (int i = 0; i < batch.size(); i++) {

			//average case requires range = theta(size).  refill batch vector with new values.
			fillArr(tmpArr, batch[0].size(), batch[0].size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			CountingSort(tmpArr, batch[0].size(), batch[0].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

		}
	}
	else if (inputCase == 3) { //worst case input
		for (int i = 0; i < batch.size(); i++) {
			//worst case requires range = Omega(size).  fill batch vector with new values.
			fillArr(tmpArr, batch[0].size(), worstRange);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			CountingSort(tmpArr, batch[0].size(), worstRange);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
	else {//userChoice[1]==4. do all
		//average, best, worst
		for (int i = 0; i < batch.size(); i++) {
			//best case: low range.  
			//filling array with low range
			fillArr(tmpArr, batch[i].size(), bestRange);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			CountingSort(tmpArr, batch[i].size(), bestRange);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);


			//average case requires range = size.  replacing tmpArr values
			fillArr(tmpArr, batch[i].size(), batch.size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			CountingSort(tmpArr, batch[i].size(), batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][1][i] = chrono::duration_cast<chrono::microseconds>(stop - start);


			//worst case requires large range.  replacing tmpArr values.
			fillArr(tmpArr, batch[i].size(), worstRange);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			CountingSort(tmpArr, batch[i].size(), worstRange);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][2][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
	return bestRange;
}

int radixSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	int algoPos = (multi) ? 7 : 0; //if all algorithms are tested, data must be sent to vector position [7] of duration, else [0]
	int inputCasePos = 0;
	int bestRange = (int)sqrt((double)batch[0].size());
	int worstRange = INT_MAX / 1000;

	if (inputCase == 1) {//best case input
		for (int i = 0; i < batch.size(); i++) {

			//best case requires low range.  fill vector with low range values.
			fillArr(batch[i], bestRange);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			RadixSort(&batch[i], batch[i].size(), bestRange);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

		}
	}
	else if (inputCase == 2) //average case input
	{
		for (int i = 0; i < batch.size(); i++) {

			//average case requires range = theta(size).  refill batch vector with new values.
			fillArr(batch[i], batch[i].size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			RadixSort(&batch[i], batch[i].size(), batch[0].size()-1);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

		}
	}
	else if (inputCase == 3) { //worst case input
		for (int i = 0; i < batch.size(); i++) {
			//worst case requires range = Omega(size).  fill batch vector with new values.
			fillArr(batch[i], worstRange);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			RadixSort(&batch[i], batch[i].size(), worstRange);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);
		}
	}
	else {//userChoice[1]==4. do all
		//average, best, worst
		for (int i = 0; i < batch.size(); i++) {
			//best case: low range.  
			//filling array with low range
			fillArr(batch[i], bestRange);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			RadixSort(&batch[i], batch[i].size(), bestRange-1);//subtracting 1 from range to lose a digit

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);


			//average case requires range = size.  replacing batch values
			fillArr(batch[i], batch.size());

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			RadixSort(&batch[i], batch[i].size(), batch[i].size());

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][1][i] = chrono::duration_cast<chrono::microseconds>(stop - start);


			//worst case requires large range.  replacing tmpArr values.
			fillArr(batch[i], worstRange);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			RadixSort(&batch[i], batch[i].size(), worstRange);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time
			duration[algoPos][2][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

			//debug
			//cout << "\nPrinting Result of Worst-Case Radix\n";
			//prntArr(batch[i]);
		}
	}
	return bestRange;
}
