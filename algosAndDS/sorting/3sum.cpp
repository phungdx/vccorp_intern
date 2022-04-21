#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


/*
Given an integer array nums, return all the triplets [nums[i], nums[l], nums[r]] 
such that i != l, i != r, and l != r, and nums[i] + nums[l] + nums[r] == 0.

Notice that the solution set must not contain duplicate triplets.

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]

Example 2:
Input: nums = []
Output: []

Example 3:

Input: nums = [0]
Output: []

link reference: https://fizzbuzzed.com/top-interview-questions-1/
*/

// Solution 1: O(n^3)
// Ta sort lại mảng để giải quyết vấn đề có các triplets có tập hợp các số giống nhau
// Đầu mỗi vòng lặp mới ta check xem số hiện tại đang xét đã được duyệt qua hay chưa,
// Như thế ta tránh gặp phải trường hợp tìm được các triplet có tập hợp các số giống nhau.
vector<vector<int>> threeSum_1(vector<int>& nums) {
    vector<vector<int>> triplets;
 
    sort(begin(nums), end(nums));
 
    for (int i = 0; i < nums.size() - 2; ++i) {
        // nếu số hiện tại đã duyệt rồi thì bỏ qua
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
 
        for (int j = i + 1; j < nums.size() - 1; ++j) {
            // nếu số hiện tại đã duyệt rồi thì bỏ qua
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }
 
            for (int k = j + 1; k < nums.size(); ++k) {
                // nếu số hiện tại đã duyệt rồi thì bỏ qua
                if (k > j + 1 && nums[k] == nums[k - 1]) {
                    continue;
                }
 
                if (nums[i] + nums[j] + nums[k] == 0) {
                    triplets.push_back(vector<int>{nums[i], nums[j], nums[k]});
                }
            }
        }
    }
 
    return triplets;
}





// Solution 2: O(n^2)
// Ta sort lại mảng để giải quyết vấn đề có các triplets có tập hợp các số giống nhau.

vector<vector<int>> threeSum_2(vector<int>& nums) {
    vector<vector<int>> triplets;
  
    // Sort lại mảng
    sort(nums.begin(),nums.end());
    
    for(int i = 0; i < nums.size(); i++){
        // skip các giá trị đã duyệt rồi
        if(i > 0 && nums[i] == nums[i-1])
            continue;

        // Tạo 2 con trỏ trái và phải của mảng tại index i+1 và n - 1
        int l = i + 1, r = nums.size() - 1;
        
        while(l < r){
        
            if(nums[i] + nums[l] + nums[r] == 0){
                triplets.push_back({nums[i], nums[l], nums[r]});
                
                int val1 = nums[l];
                // skip tất cá các giá trị đã duyệt rồi
                while( l < r && nums[l] == val1) l++;
                    
                
                int val2 = nums[r];
                // skip tất cá các giá trị đã duyệt rồi
                while(l < r && nums[r] == val2) r--;
                
            }
                
            // Tổng 3 số < 0 thì cần tăng giá trị lên -> dịch pointer l sang phải
            else if(nums[i] + nums[l] + nums[r] < 0)  l++;
                
            // Tổng 3 số > 0 thì cần giảm giá trị đi -> dịch pointer r sang trái
            else if(nums[i] + nums[l] + nums[r] > 0)  r--;
              
        }
    }
    
    return triplets;
}


int main(){
    vector<int> nums1 = {-1,0,1,2,-1,-4};
    vector<vector<int>> triplets = threeSum_1(nums1);
    for(auto triplet : triplets){
        for(auto e: triplet){
            cout << e << ' ';
        }
        cout << '\n';
    }
    return 0;
}