#pragma once
//Heap sort

#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>    
#include <array>        
#include <random>       
#include <chrono>
#include <ctime>

//Function generates a sorted array containing DISTINCT values [1,2,3,4...size] and then randomly suffles the values  
void Shuffle_Array(int arr[], int n) //Function does not produce an array, randomly shuffles an existing array
{

    // To obtain a time-based seed 
    unsigned seed = 0;

    // Shuffling our array 
    std::shuffle(arr, arr + n,
        std::default_random_engine(seed));
}
void Generate_LinearShuffledArray(int array[], int size)
{
    int num = 0;
    for (int i = 0; i < size; i++)
    {
        array[i] = ++num;
    }

    Shuffle_Array(array, size);
}

//Heap sort function
class MaxHeap
{
public: //FIXED ERROR: isEmpty is inaccesable
    int size{};
    std::vector<int> array = { -1 }; //use index 0 as some junk value

    int parent(int i) //find parent node of index
    {
        return i / 2;
    }

    int leftChild(int i) //find left node of index 
    {
        return 2 * i;
    }

    int rightChild(int i) //find right node of index
    {
        return (2 * i) + 1;
    }

    bool isEmpty() const //checks if list is empty
    {
        return size == 0;
    }

    int getMax() const //find the root
    {
        return array[1];
    }

    void Insert(int val)
    {
        if (size + 1 >= array.size()) //check if a value can be inserted
        {
            array.push_back(0);
        }
        array[++size] = val;//increment the size of max heap
        HeapifyUp(size);
        return;
    }

    void HeapifyUp(int i) //MAX HEAPIFYup 
    {
        if (i > size) //check if we can shift up an index
        {
            return;
        }
        if (i == 1) {
            return;
        }
        if (array[i] > array[parent(i)])
        {
            std::swap(array[parent(i)], array[i]); //CHANGED FORM CONVENTIONAL SWAP USING TEMP
        }
        HeapifyUp(parent(i)); //recusive call to check if heap maintain property
    }

    int ExtractMax() //this mehtod returns a value
    {
        int maxValue = array[1]; //Store root value before we swap values array[1] <=> array[size]
        std::swap(array[1], array[size]); //swap root (largest value) with the last node (smallest value) in the heap
        size--; //reduce heap size by 1
        HeapifyDown(1); //Heapify starting at the root
        return maxValue; //return the root value (which always stores the max)
    }

    void HeapifyDown(int i) //HEAPIFY
    {
        if (i > size)
        {
            return;
        }

        int max = i;

        if (leftChild(i) <= size && array[i] < array[leftChild(i)]) //check left child
        {
            max = leftChild(i);
        }
        if (rightChild(i) <= size && array[max] < array[rightChild(i)]) //check right child
        {
            max = rightChild(i);
        }

        if (max != i) //if a child was greater than the parent swap and continue heapfying
        {
            std::swap(array[i], array[max]);
            HeapifyDown(max);
        }

        return; //parent is larger than children or i > heapSize, no more swaps are needed
    }

    void modifyKey(int val, int i)
    {
        if (i > size || val < array[i]) //bigger keys must be used. This will also prevent a smaller value from being inserted into the root
        {
            std::cout << "Error: index is out of bounds or the entered value is less than the current key.\n";
        }
        else
        {
            array[i] = val; //insert the new value at specified index

            while (i > 1 && array[parent(i)] < array[i]) //keep swapping values up towards the root if parent is greater MODIFY COMPARISON FOR MIN VERSION
            {
                std::swap(array[i], array[parent(i)]);
                i = parent(i); //check the next parent node
            }
        }
    }

    void printMaxHeap() //FIXED ERROR: Tried to pass maxHeap* as a parameter. This wasn't needed since array and size can be accssed dirctly within the class
    {
        for (int i = 1; i <= size; i++)
        {
            std::cout << array[i] << ", ";
        }std::cout << std::endl;
    }

    void printSortedArray() //FIXED ERROR: Tried to pass maxHeap* as a parameter. This wasn't needed since array and size can be accssed dirctly within the class
    {
        for (int i = 1; i < array.size() - size; i++)
        {
            std::cout << array[i] << ", ";
        }std::cout << std::endl;
    }

    void HeapSort()
    {
        for (int i = size; i >= 2; i--)
        {
            std::swap(array[1], array[i]);
            size--;
            HeapifyDown(1); //Heapify downwards starting at the root to get the next largest value
        }
    }

};


/*
int main()
{
    //[Make changes here] Array parameters
    int n = 1000;     //n = SIZE of the array

//Generate the array
    int* randomArray = new int[n];
    Generate_LinearShuffledArray(randomArray, n);

    //Build the heap
    MaxHeap* maxHeap = new MaxHeap();
    for (int i = 0; i < n; i++)
    {
        maxHeap->Insert(randomArray[i]);
    }

    //[Optional] Print heap BEFORE sorting
    //maxHeap->printMaxHeap();

//Test and time heap sort function========================================================================
    auto start = std::chrono::steady_clock::now();      //Start clock

    maxHeap->HeapSort();                                //Function call

    auto end = std::chrono::steady_clock::now();        //End clock, print time
    std::cout << "Time: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << " microseconds" << std::endl;

    //[Optional] Print heap AFTER sorting
    //maxHeap->printSortedArray();
}
*/