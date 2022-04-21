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
        // Tìm vị trí ở giữa
        mid = start + (end - start) / 2;

        // nếu vị trí giữa bằng target thì return index của nó
        if(nums[mid] == target){
            return mid;
        }
        
        // so sánh vị trí đầu đoạn và giữa đoạn, xem có phải đoạn tăng dần không.
        if(nums[start] <= nums[mid]){
            // xem target có thuộc đoạn tăng dần đó không
            if(nums[start] <= target && target <= nums[mid]){
                // Nếu có ta thu hẹp đoạn cần tìm kiếm lại
                end = mid - 1;
            }

            // Nếu target không thuộc đoạn tăng dần thì nó sẽ thuộc đoạn còn lại,
            // tức là đoạn bên phải số giữa. Ta thu hẹp đoạn cần tìm kiếm lại.
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