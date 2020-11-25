#pragma once
//Counting sort

#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>    
#include <array>        
#include <random>       
#include <chrono>
#include <ctime>


//Function generates a test array within a specified range
void Generate_RandomArray(int array[], int size, int range)
{
    range++;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distribution(1, range); //range = max possible value in the array

    for (int i = 0; i < size; i++)
    {
        array[i] = distribution(gen);
    }
}

//Counting sort function
void CountingSort(int A[], int n, int max)  //if array has 5 elements length should be 5, max is the biggest value in the array
{
    //(count array) Make an auxillary array C of size max + 1, Will hold the range of digits and their frequencies (count)
    std::vector<int> C(max + 1);

    //(output array) Make an auxiallary array B of size n (will hold the sorted values from the input array)
    std::vector<int> B(n + 1); //FIXED ERROR: Changing the size of array B to accommodate one value more than the input array fixed the issue
                                //Changed std::vector<int> B(n) to std::vector<int> B(n + 1)
                                //Treat index 0 as a garbage value

    //Initialize all elements in array C to 0
    for (int num : C)
    {
        num = 0;
    }

    //count the frequencies of the keys in the input array A, store the count in array C
    for (int i = 0; i < n; i++)
    {
        C[A[i]] = C[A[i]] + 1; //increment the frequency of the key by 1
    }

    //cumulatively add the values in array C (add previous value to current value, start at index 1)
    for (int j = 1; j < C.size(); j++)
    {
        C[j] = C[j - 1] + C[j];
    }

    for (int r = n - 1; r >= 0; r--) //Fixed issue: last accumulated value in the array count will always be out of bounds if array B is initialized to same size input array A (n);
    {

        B[C[A[r]]] = A[r]; //Fixed error
        C[A[r]] = C[A[r]] - 1; //decrement

    }

    //TEST: print the output array
    /*for (int i = 1; i <= n; i++)
    {
       std::cout << B[i] << ", ";
    }*/

    //copy the output array into the input array
    for (int i = 0, j = 1; j <= n; i++, j++)
    {
        A[i] = B[j];
    }
}

//[Optional] Functon prints the array
void PrintArray(int array[], int size)
{
    std::cout << "Array before sorting: \n";
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << ", ";
    }
}


/*
int main()
{
    //[Make changes here] Array parameters
    int n = 1000;           //n = SIZE of the array
    int range = 10;         //MAX VALUE in the array

//Generate the array
    int* randomArray = new int[n];
    Generate_RandomArray(randomArray, n, range);


    //Test and time counting sort function========================================================================
    auto start = std::chrono::steady_clock::now();  //Start clock

    CountingSort(randomArray, n, range);            //Function call

    auto end = std::chrono::steady_clock::now();    //End clock, Print time
    std::cout << "Time: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << " microseconds" << std::endl;

    //[Optional] Print the sorted array
    //PrintArray(randomArray, n);
}
*/