#include<iostream>
using namespace std;

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