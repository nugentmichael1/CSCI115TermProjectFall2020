/*
* CSCI 115 - Term Project: Comparison of Sorting Algorithms
*
* Team Members: Emmanuel Cardenas, Ashley Taylor Diaz, Narendra Mannan, Michael Nugent, Kalvin Xiong, and Austin Wing
* 
* Dec. 1st, 2020
* 
* Compiled in Windows Visual Studio 2019
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
#include "quickSort.h" //quickSort
#include "heapSort.h" //heapSort
#include "countingSort.h"//countingSort
#include "radixSort.h" //radixSort
#include "auxiliary.h" //supportive functions like random number generator and header formatting.
#include "testing.h" //functions to test each algorithm

using namespace std;

int main() {

	//initializations
	int size = 0,
		range = 10000;
	int batches = 0;
	int sorts = 1;
	int sizeCases = 0;
	int inputCases = 1;
	int bestRange = 0;//holds range value calculated by non-comparison sorts (counting & radix) for best input-case

	//quicksort should be excluded if input size exceeds 5,500.
	bool excludeQSFlag = false;

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

	//quickSort case.  can cause stack overflow in worst-case: first element pivot and reverse sorted array
	if (userChoice[0] == 5) {
		while (userChoice[2] < 1 || userChoice[2]>5500) {
			cout << "Please choose an input size:\n";
			cout << "(1) - 1,000\n";
			cout << "(2) - 3,000\n";
			cout << "(3) - 5,500\n";
			cout << "Or manually input a size.  Note: QuickSort will overflow the stack on input sizes above 5,500.\n";
			cin >> userChoice[2];
		}
		//update size variable based on user input
		//quicksort case
		if (userChoice[2] == 1)size = 1000;
		else if (userChoice[2] == 2)size = 3000;
		else if (userChoice[2] == 3)size = 5500;
		else size = userChoice[2];
	}

	//Inform user of input size options and query for decision.
	//all cases other than soley quickSort
	while (userChoice[2] < 1) {
		cout << "Please choose an input size:\n";
		cout << "(1) - 1,000\n";
		cout << "(2) - 10,000\n";
		cout << "(3) - 100,000\n";
		cout << "Or manually input a size.\n";
		cin >> userChoice[2];
	}
	//update size variable with user selection
	if (userChoice[2] == 1)size = 1000;
	else if (userChoice[2] == 2)size = 10000;
	else if (userChoice[2] == 3)size = 100000;
	else size = userChoice[2];
	if (size > 5500 && (userChoice[0] == 9)) {
		cout << "Warning: QuickSort will overflow the stack on size inputs above 5,500.  Excluding it from tests.\n\n";
		excludeQSFlag = true;
	}



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

	//quickSort execution times storage
	//can clean this up by resizing when not used or vice versa: resizing when used
	vector<vector<vector<chrono::microseconds>>> quickSortDuration(3,//pivot types
		vector<vector<chrono::microseconds>>(inputCases,//# of input cases chosen by user.  1 xor 3.
			vector<chrono::microseconds>(batches)));//# of batches.  user defined.


	//vector to hold results of comparison counters in insertion sort and heap sort.
	vector<int> comparisons(batch.size());




	//generate random arrays based on number of batches user indicates
	srand(time(NULL)); //seed random number generator
	for (int i = 0; i < batch.size(); i++) fillArr(batch[i], range);



	/*Display "Execution times" header prior to algorithm if-tree in order to also display the correct 
	sorting algorithm name.  This saves cost of implementing the same if-tree later when returning results.
	*/
	cout << "\n\n -- Execution times (microseconds) -- \n";





	//main if-tree of sorting algorithm implementations.
	//1st 8 if-statements are for implementing a single choice.
	//9th if-statement is for implementing all 8 algorithms. 
	if (userChoice[0] == 1) { //insertion
		cout << "Insertion Sort\n";
		comparisons = insertionSortTest(batch, userChoice[1], duration);
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
		quickSortTest(batch, userChoice[1], quickSortDuration, false);
	}
	else if (userChoice[0] == 6) {//heap
		cout << "Heap Sort\n";
		comparisons = heapSortTest(batch, duration, false);
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
		tmp.assign(batch.begin(), batch.end());
		if (!excludeQSFlag) quickSortTest(tmp, userChoice[1], quickSortDuration, true);

		//heapSort
		tmp.assign(batch.begin(), batch.end());
		heapSortTest(tmp, duration, true);

		//countingSort
		bestRange = countingSortTest(batch, userChoice[1], duration, true);

		//radixSort
		radixSortTest(batch, userChoice[1], duration, true);
	}









	//return results to user by updating display with appropriate format and information.
	/*1st if-statement is to display the results of all 8 sorting algorithms
	* the remaining two if-statements are to return the results of 1 sorting algorithm, but accomodates 
	* quicksort's special use of all 3 pivot types, 
	*/

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
			if (size <= 5500) {
				cout << "\nQuick Sort";
				cout << "\nBest-Case\t\t\tPivot-Types\n";
				cout << "Batch\t\tFirst-Element\tRandom-Element\tMedian-Element\n";
				for (int i = 0; i < batch.size(); i++) {
					cout << i << "\t\t" << quickSortDuration[0][0][i].count() << "\t\t" << quickSortDuration[1][0][i].count() << "\t\t" << quickSortDuration[2][0][i].count() << "\n";
				}
				cout << "Average-Case\n";
				cout << "Batch\t\tFirst-Element\tRandom-Element\tMedian-Element\n";

				for (int i = 0; i < batch.size(); i++) {
					cout << i << "\t\t" << quickSortDuration[0][1][i].count() << "\t\t" << quickSortDuration[1][1][i].count() << "\t\t" << quickSortDuration[2][1][i].count() << "\n";
				}
				cout << "Worst-Case\n";
				cout << "Batch\t\tFirst-Element\tRandom-Element\tMedian-Element\n";

				for (int i = 0; i < batch.size(); i++) {
					cout << i << "\t\t" << quickSortDuration[0][2][i].count() << "\t\t" << quickSortDuration[1][2][i].count() << "\t\t" << quickSortDuration[2][2][i].count() << "\n";
				}
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
			if (size <= 5500) {
				cout << "\nQuick Sort\n";
				if (userChoice[1] == 1)cout << "Best-Case";
				else if (userChoice[1] == 2)cout << "Average-Case";
				else cout << "Worst-Case";
				cout << "\t\tPivot-Types\n";
				cout << "Batch\tFirst-Element\tRandom-Element\tMedian-Element\n";
				for (int i = 0; i < batch.size(); i++) {
					cout << i << "\t" << quickSortDuration[0][0][i].count() << "\t\t" << quickSortDuration[1][0][i].count() << "\t\t" << quickSortDuration[2][0][i].count() << "\n";
				}
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
	//quickSort
	else if (userChoice[0] == 5 && size <= 5500) {
		if (userChoice[1] == 4) {
			cout << "Best-Case\t\t\tPivot-Types\n";
			cout << "Batch\t\tFirst-Element\tRandom-Element\tMedian-Element\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t\t" << quickSortDuration[0][0][i].count() << "\t\t" << quickSortDuration[1][0][i].count() << "\t\t" << quickSortDuration[2][0][i].count() << "\n";
			}
			cout << "Average-Case\n";
			cout << "Batch\t\tFirst-Element\tRandom-Element\tMedian-Element\n";

			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t\t" << quickSortDuration[0][1][i].count() << "\t\t" << quickSortDuration[1][1][i].count() << "\t\t" << quickSortDuration[2][1][i].count() << "\n";
			}
			cout << "Worst-Case\n";
			cout << "Batch\t\tFirst-Element\tRandom-Element\tMedian-Element\n";

			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t\t" << quickSortDuration[0][2][i].count() << "\t\t" << quickSortDuration[1][2][i].count() << "\t\t" << quickSortDuration[2][2][i].count() << "\n";
			}
		}
		else {//one input-case
			if (userChoice[1] == 1)cout << "Best-Case";
			else if (userChoice[1] == 2)cout << "Average-Case";
			else cout << "Worst-Case";
			cout << "\t\tPivot-Types\n";
			cout << "Batch\tFirst-Element\tRandom-Element\tMedian-Element\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << quickSortDuration[0][0][i].count() << "\t\t" << quickSortDuration[1][0][i].count() << "\t\t" << quickSortDuration[2][0][i].count() << "\n";
			}

		}

	}

	//only 1 algorithm selected; not quicksort
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
		//only selection or heap
		else if (userChoice[0] == 2 || userChoice[0] == 6) {
			cout << "Batch\tBest-Case = Average-Case = Worst-Case\n";
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t\t\t" << duration[0][0][i].count() << "\n";
			}
			if (userChoice[0] == 6) {
				cout << "Comparisons:\n";
				for (int i = 0; i < batch.size(); i++) {
					cout << i << "\t\t" << comparisons[i] << "\n";
				}
			}

		}
		//only 1 input-case.  not selection or heap
		else {
			header(userChoice[1]);
			for (int i = 0; i < batch.size(); i++) {
				cout << i << "\t" << duration[0][0][i].count() << "\n";
			}
			if (userChoice[0] == 7 || userChoice[0] == 8) rangeFormat(userChoice[1], bestRange, batch[0].size());
			if (userChoice[0] == 1) {
				cout << "Comparisons:\n";
				for (int i = 0; i < batch.size(); i++) {
					cout << i << "\t" << comparisons[i] << "\n";
				}
			}

		}
	}
	cout << "\nn = " << size << "\n";

}