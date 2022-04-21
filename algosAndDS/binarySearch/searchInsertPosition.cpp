#include<iostream>
#include<vector>
using namespace std;

/*
There is an integer array nums sorted in aschighing order (with distinct values).

Prior to being passed to your function, nums is possibly rotated
at an unknown pivot index k (1 <= k < nums.length) 
such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, 
return the index of target if it is in nums, 
or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.


Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:
Input: nums = [1], target = 0
Output: -1

*/


// Solution O(log(n))
// Sử dụng binary search
// Trong trường hợp target tồn tại trong mảng thì khá rõ ràng
// Trường hợp target không có trong mảng thì cần return chỉ số index hợp lý
// của nó nếu chèn nó vào mảng
// Nếu target không có trong mảng thì ở bước xét cuối cùng có chỉ số low == mid == high
// ta tiếp tục qúa trình tính toán thì lúc này low > high, ta nhận thấy low luôn chỉ vào vị trí của số
// mà ta cần tìm trong mọi trường hợp (dù cho target có lớn hơn nums[mid] hay nhỏ hơn nums[mid]),
// vì vậy trong trường hợp ko có target trong mảng thì giá trị cuối cùng của low chính là
// vị trí của số mới mà ta chèn vào.

int searchInsert(vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;
    int mid;
    while(low <= high){
        // Tìm vị trí giữa đoạn
        mid = low + (high - low)/2;

        // Nếu sô giữa bằng target thì return index của nó
        if(nums[mid] == target) return mid;

        // nếu số giữa lớn hơn target -> target có thể nằm ở đoạn bên trái số giữa
        else if(nums[mid] > target) high = mid - 1;

        // nếu số giữa nhỏ hơn target -> target có thể nằm ở đoạn bên phải số giữa
        else low = mid + 1;
    }
    // trường hợp ko có target trong mảng --> return vị trí của nó nếu đc thêm vào
    return low;
}

int main(){
    vector<int> arr = {1,3,5,6};
    int target = 2;
    cout << searchInsert(arr, target);

    return 0;
}