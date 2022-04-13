#include<iostream>
using namespace std;

int binarySearchIterative(int A[], int n, int x){
    int start = 0;
    int end = n - 1;
    while(start <= end){
        int mid = start + (end - start) / 2;
        if (A[mid] == x) return mid;
        else if (x < A[mid]) end = mid - 1;
        else start = mid + 1;
    }
    return -1;
}

int binarySearchRecursive(int A[], int start, int end, int x){
    int mid = start + (end - start) / 2;
    if(A[mid] == x) return mid;
    else if(A[mid] > x) return binarySearchRecursive(A, start, mid - 1, x);
    else return binarySearchRecursive(A, mid + 1, end, x);
}


int main(){
    int arr[] = {0,1,2,2,3,3,7,8,9};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << binarySearchIterative(arr, n, 9) << '\n';
    cout << binarySearchRecursive(arr, 0, n, 9) << '\n';
    return 0;
}