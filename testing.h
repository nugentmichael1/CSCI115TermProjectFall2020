#pragma once


//functions to test respective sorting algorithms and store execution times
vector<int> insertionSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration);
void selectionSortTest(vector<vector<int>>& batch, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
void bubbleSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
void mergeSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
void quickSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& qSduration, bool multi);
vector<int> heapSortTest(vector<vector<int>>& batch, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
int countingSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);
int radixSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi);


vector<int> insertionSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	//store number of comparisons made
	vector<int> comparisons(batch.size());

	if (inputCase == 1) {//best case input
		for (int i = 0; i < batch.size(); i++) {

			//make temporary copy of input array to preserve original.
			vector<int> tmp(batch[i]);

			//sort tmp array to create best insertion case input
			insertionSort(tmp);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//sort
			comparisons[i] = insertionSort(tmp);

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
			comparisons[i] = insertionSort(tmp);

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
			comparisons[i] = insertionSort(tmp);

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
	return comparisons;
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

void quickSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& qSDuration, bool multi) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	//int algoPos = (multi) ? 4 : 0; //if all algorithms are tested, data must be sent to vector position [4] of duration, else [0]

	//int array to comply with quickSort()'s parameters
	int* tmpArr = new int[batch[0].size()];

	//will do all three pivot types for each case

	//input-case: best
	if (inputCase == 1) {
		for (int i = 0; i < batch.size(); i++) {

			//copy vector array to int array
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//sort array to create best case
			quick_sort(tmpArr, 0, batch[i].size() - 1, 1);

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "first element"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 1);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[0][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: first element;input-case: best; batch i


			//copy vector array to int array
			//for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];
			//re-use sorted array

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "random"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 2);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[1][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: random;input-case: best; batch i



			//copy vector array to int array
			//for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];
			//re-use sorted array

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "median of first, middle, and last"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 3);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[2][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: median; input case: best; batch i
		}
	}
	//average case
	else if (inputCase == 2) {
		for (int i = 0; i < batch.size(); i++) {

			//copy vector array to int array
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "first element"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 1);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[0][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: first element; input-case;batch i


			//copy vector array to int array
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "random"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 2);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[1][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: random; input-case; batch i



			//copy vector array to int array
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "median of first, middle, and last"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 3);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[2][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: median; input-case; batch i
		}
	}
	//worst case
	else if (inputCase == 3) {
		for (int i = 0; i < batch.size(); i++) {

			//copy vector array to int array
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//creat worst case by reversing sorted array
			//1) sort array
			quick_sort(tmpArr, 0, batch[i].size() - 1, 1);
			//2) reverse sorted array
			for (int j = 0, k = batch[i].size() - 1; j < k / 2; j++, k--) {
				int swapTmp = tmpArr[j];
				tmpArr[j] = tmpArr[k];
				tmpArr[k] = swapTmp;
			}
			//store copy of reverse sorted array to use with other pivot-types
			int* tmpArr2 = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) tmpArr2[j] = tmpArr[j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "first element"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 1);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[0][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: first element;input-case batch i


			//copy reversed sorted array to tmp array
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = tmpArr2[j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "random"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 2);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[1][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: random;input-case; batch i



			//copy vector array to int array
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = tmpArr2[j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "median of first, middle, and last"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 3);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[2][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: input-case;median; batch i
		}
	}
	//all 3 input-cases
	else {
		for (int i = 0; i < batch.size(); i++) {
			//average case
			//copy vector data to int array to comply with quick_sort parameters
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot-type: "first element"
			quick_sort(tmpArr, 0, batch[i].size(), 1);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution times
			qSDuration[0][1][i] = chrono::duration_cast<microseconds>(stop - start);//average case,first element pivot, batch i


			//restore array to original unsorted state
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot-type: "random"
			quick_sort(tmpArr, 0, batch[i].size(), 2);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution times
			qSDuration[1][1][i] = chrono::duration_cast<microseconds>(stop - start);//average case,random pivot, batch i



			//restore array to original unsorted state
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot-type: "median of first, middle, and last elements"
			quick_sort(tmpArr, 0, batch[i].size(), 3);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution times
			qSDuration[2][1][i] = chrono::duration_cast<microseconds>(stop - start);//average case,median pivot, batch i


			//best case.  there is no difference between best and average cases now.  might change in future.
			//copy vector data to int array to comply with quick_sort parameters
			//for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot-type: "first element"
			quick_sort(tmpArr, 0, batch[i].size(), 1);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution times
			qSDuration[0][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: first; input case: average; batch i


			//restore array to original unsorted state
			//for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot-type: "random"
			quick_sort(tmpArr, 0, batch[i].size(), 2);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution times
			qSDuration[1][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: random; input case: average; batch i



			//restore array to original unsorted state
			//for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = batch[i][j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot-type: "median of first, middle, and last elements"
			quick_sort(tmpArr, 0, batch[i].size(), 3);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution times
			qSDuration[2][0][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: median; input case: average; batch i



			//creat worst case by reversing sorted array
			//1) array is already sorted from last set of tests
			//2) reverse sorted array
			for (int j = 0, k = batch[i].size() - 1; j < k / 2; j++, k--) {
				int swapTmp = tmpArr[j];
				tmpArr[j] = tmpArr[k];
				tmpArr[k] = swapTmp;
			}
			//store copy of reverse sorted array to use with other pivot-types
			int* tmpArr2 = new int[batch[i].size()];
			for (int j = 0; j < batch[i].size(); j++) tmpArr2[j] = tmpArr[j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "first element"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 1);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[0][2][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: first; input case: worst; batch i


			//copy reversed sorted array to tmp array
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = tmpArr2[j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "random"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 2);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[1][2][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: random; input case: worst; batch i



			//copy vector array to int array
			for (int j = 0; j < batch[i].size(); j++) tmpArr[j] = tmpArr2[j];

			//start stopwatch
			start = chrono::high_resolution_clock::now();

			//pivot: "median of first, middle, and last"
			quick_sort(tmpArr, 0, batch[i].size() - 1, 3);

			//stop stopwatch
			stop = chrono::high_resolution_clock::now();

			//record execution time;
			qSDuration[2][2][i] = chrono::duration_cast<microseconds>(stop - start);//pivot-type: median; input case: worst; batch i

		}
	}
}

vector<int> heapSortTest(vector<vector<int>>& batch, vector<vector<vector<chrono::microseconds>>>& duration, bool multi) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	int algoPos = (multi) ? 5 : 0; //if all algorithms are tested, data must be sent to vector position [5] of duration, else [0]

	//comparisons tracker
	vector<int> comparisons(batch.size());

	//all input-cases result in identical outputs
	for (int i = 0; i < batch.size(); i++) {

		MaxHeap tmp;
		for (auto a : batch[i])tmp.Insert(a);


		//start stopwatch
		start = chrono::high_resolution_clock::now();

		//sort
		comparisons[i] = tmp.HeapSort();

		//stop stopwatch
		stop = chrono::high_resolution_clock::now();

		duration[algoPos][0][i] = chrono::duration_cast<chrono::microseconds>(stop - start);

		//debug
		//cout << "\nPrinting heapSort result\n";
		//tmp.printSortedArray();
	}
	return comparisons;
}

int countingSortTest(vector<vector<int>>& batch, int inputCase, vector<vector<vector<chrono::microseconds>>>& duration, bool multi) {
	//initialize stopwatch variables to measure execution times
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point stop;

	int algoPos = (multi) ? 6 : 0; //if all algorithms are tested, data must be sent to vector position [6] of duration, else [0]
	int inputCasePos = 0;
	int bestRange = (int)sqrt((double)batch[0].size());
	int worstRange = INT_MAX / 1000;

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
			RadixSort(&batch[i], batch[i].size(), batch[0].size() - 1);

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
			RadixSort(&batch[i], batch[i].size(), bestRange - 1);//subtracting 1 from range to lose a digit

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
