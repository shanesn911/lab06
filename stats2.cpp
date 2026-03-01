#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

void bubbleSort(int *array, int size);
double average(int *array, int size);
double median(int* array, int size);
double stddev(int* array, int size);

int main(){
	cout << fixed << showpoint;
	cout << setprecision(2);

	string filename;
	cout << "Enter filename: ";
	cin >> filename;

	ifstream inFile(filename);
	if(!inFile.is_open()){
		cerr << "Cannot open " << filename << endl;
		exit(1);
	}

	// Count number of grades for dynamic allocation
	int count = 0;
	int val;
	while(inFile >> val){
		count++;
	}
	inFile.close();

	if(count == 0){
		return 0;
	}

	// Fill array with grade values
	inFile.open(filename);
	int* grades = new int[count];
	for(int i = 0; i < count; i++){
		inFile >> grades[i];
	}
	inFile.close();

	bubbleSort(grades, count);

	// Display calculated stats
	cout << "Here are some statistics:" << endl;
	cout << "      N: " << count << endl;
	cout << "Average: " << average(grades, count) << endl;
	cout << " Median: " << median(grades, count) << endl;
	cout << " StdDev: " << stddev(grades, count) << endl;

	delete[] grades;
	return 0;
}

void bubbleSort(int *array, int size){
	int temp;
	// Classic bubble sort logic
	for(int i = size - 1; i >= 0; i--){
		for(int j = 1; j <= i; j++){
			if(array[j - 1] > array[j]){
				temp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = temp;
			}
		}
	}
}

double average(int *array, int size){
	double sum = 0.0;
	for(int i = 0; i < size; i++){
		sum += array[i];
	}
	return sum / size;
}

double median(int* array, int size){
	// Calculate middle point based on even/odd size
	if(size % 2 == 0){
		return (array[size / 2 - 1] + array[size / 2]) / 2.0;
	}else{
		return (double)array[size / 2];
	}
}

double stddev(int* array, int size){
	if(size == 1) return 0.0;
	double avg = average(array, size);
	double sumSqDiff = 0.0;
	// Calculate sum of squared differences
	for(int i = 0; i < size; i++){
		double diff = array[i] - avg;
		sumSqDiff += diff * diff;
	}
	// Square root of sample variance
	return sqrt(sumSqDiff / (size - 1));
}