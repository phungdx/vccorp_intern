#include<iostream>
#include "sort.h"
using namespace std;

/*
BUBBLE SORT
*/
void bubbleSort(int *arr, int n){
    bool isSwapped;
    for(int i = 0; i < n; ++i){
        isSwapped = false;
        for(int j = 0; j < n - 1; ++j){
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }

        if(isSwapped == false){
            break;
        }
    }
}

/*
SELECTION SORT
*/
void selectionSort(int arr[], int n){
    int minIndex;
    for(int i = 0; i < n; ++i){
        minIndex = i;
        for(int j = i + 1; j < n; ++j){
            if(arr[minIndex] > arr[j]){
                minIndex = j;
            }
        }
        swap(arr[minIndex], arr[i]);
    }
}

/*
INSERTION SORT
*/
void insertionSort(int arr[], int n){
    int min, j;
    for(int i = 0; i < n; ++i){
        min = arr[i];
        j = i - 1;
        while(j >= 0 & arr[j] > min){
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = min;
    }
}

/*
MERGE SORT
*/
// void mergeSort(int arr[], int n){

// }

/*
QUICK SORT
*/
int partition(int arr[],int left, int right){
    int pivot = arr[right];
    int i = left - 1;
    for(int j = left; j < right; ++j){
        if(arr[j] < pivot){
            i += 1;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[right]);

    return i + 1;
}

void quickSort(int arr[], int left, int right){
    if(left > right){
        return;
    }
    int index_pivot = partition(arr, left, right);
    quickSort(arr, left, index_pivot - 1);
    quickSort(arr, index_pivot + 1, right);
}


/*
HEAP SORT
*/
// void heapSort(int arr[], int n){

// }

int main(){
    int arr[] = {7,5,6,4,3,2,1,9,8};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n-1);

    for (auto item: arr)
	{
		cout << item << " ";
	}
	cout << endl;

    return 0;
}