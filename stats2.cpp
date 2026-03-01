//stats2.cpp
//Author: Shane Nguyen
//Date: February 2026
//Description: Reads integer grades from a file specified by the user,
//             then calculates and displays N, average, median, and
//             standard deviation of those grades.

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

//FUNCTION DECLARATIONS: YOU MUST USE THESE (do not remove):
void bubbleSort(int *array, int size);
double average(int *array, int size);
double median(int* array, int size);
double stddev(int* array, int size);

int main(){
    cout << fixed << showpoint;
    cout << setprecision(2);

    //get filename from user and open the file
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if(!inFile.is_open()){
        cerr << "Cannot open " << filename << endl;
        exit(1);
    }

    //count how many integers are in the file
    int count = 0;
    int val;
    while(inFile >> val){
        count++;
    }

    //handle empty file
    if(count == 0){
        inFile.close();
        return 0;
    }

    //allocate a dynamic array of that size
    int* grades = new int[count];

    //rewind and read values into the array
    inFile.clear();
    inFile.seekg(0);
    for(int i = 0; i < count; i++){
        inFile >> grades[i];
    }
    inFile.close();

    //sort the array
    bubbleSort(grades, count);

    //print results
    cout << "Here are some statistics:" << endl;
    cout << "      N: " << count << endl;
    cout << "Average: " << average(grades, count) << endl;
    cout << " Median: " << median(grades, count) << endl;
    cout << " StdDev: " << stddev(grades, count) << endl;

    //deallocate dynamic array
    delete[] grades;

    return 0;
}

//Pre-Condition:  Takes in a dynamic int array and its size
//Post-Condition: Sorts the array in ascending order of its values
void bubbleSort(int *array, int size){
    int temp;
    for(int i = size - 1; i >= 0; i--){
        for(int j = 1; j <= i; j++){
            if(array[j-1] > array[j]){
                temp = array[j-1];
                array[j-1] = array[j];
                array[j] = temp;
            }
        }
    }
}

//Pre-Condition:  Takes in a dynamic int array and its size
//Post-Condition: Returns the arithmetic mean of the array elements
double average(int *array, int size){
    double sum = 0.0;
    for(int i = 0; i < size; i++){
        sum += array[i];
    }
    return sum / size;
}

//Pre-Condition:  Takes in a sorted dynamic int array and its size
//Post-Condition: Returns the median value of the array
double median(int* array, int size){
    if(size % 2 == 0){
        return (array[size / 2 - 1] + array[size / 2]) / 2.0;
    }else{
        return array[size / 2];
    }
}

//Pre-Condition:  Takes in a dynamic int array and its size
//Post-Condition: Returns the sample standard deviation of the array
double stddev(int* array, int size){
    if(size == 1){
        return 0.0;
    }

    double avg = average(array, size);
    double sumSquaredDiffs = 0.0;

    for(int i = 0; i < size; i++){
        double diff = array[i] - avg;
        sumSquaredDiffs += diff * diff;
    }

    double variance = sumSquaredDiffs / (size - 1);
    return sqrt(variance);
}