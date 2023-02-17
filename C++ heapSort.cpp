// Samuel Monteiro Basso           100379716
// 2022-06-20
// this is my heapsort program, that given a list of integers, it sorts them in ascending order using the heapSprt algorithm

#include <iostream>

// This function heapifies the array.
void heapify(int A[], int n, int i)
{
    int largest = i;
    int left = (2 * i) + 1; 
    int right = (2 * i) + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

// use max-heap data structure
void heapSort(int A[], int n) {
   
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(A, n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(A[0], A[i]);
        heapify(A, i, 0);
    }
}

// This void function prints the array.
void print(int A[],int n) {
	for (int i = 0; i < n; i++) {
		std::cout << A[i] << ", ";
	}
}

int main() {

	int data[] = { 13, 10, 14, 4, 7, 6 };
	int n = sizeof(data)/sizeof(data[0]);
	std::cout << "Before sorting array is: ";
	print(data,n);
	std::cout << std::endl;
	std::cout << "After sorting array is: ";
    	heapSort(data, n);
	print(data, n);
	std::cout << std::endl;

	return 0;
}
