#include<iostream>
#include<vector>
using namespace std;

/*
Sử dụng binary search

*/

int search(vector<int>& nums, int target) {
    int start = 0;
    int end = nums.size() - 1;
    int mid;
    while(start <= end){
        mid = start + (end - start) / 2;
        if(nums[mid] == target){
            return mid;
        }
        
        if(nums[start] <= nums[mid]){
            if(nums[start] <= target && target <= nums[mid]){
                end = mid - 1;
            }
            else{
                start = mid + 1;
            }
        }
        
        else{
            if(target >= nums[mid] && target <= nums[end]){
                start = mid + 1;
            }          
            else{
                end = mid - 1;
            }
        }
        
    }
    return -1;
    
}



int main(){
    vector<int> arr = {4,5,6,7,0,1,2};
    vector<int> arr_ = {0,1,2,4,5,6,7};

    int n = arr.size();
    int target = 0;
    cout << search(arr, target) << '\n';

    return 0;
}