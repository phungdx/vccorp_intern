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
*/

// Solution
// 
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> triplets;
  
    sort(nums.begin(),nums.end());
    
    for(int i = 0; i < nums.size(); i++){
        if(i > 0 && nums[i] == nums[i-1])
            continue;

        int l = i+1, r = nums.size()-1;
        
        while(l < r){
        
            if(nums[i] + nums[l] + nums[r] == 0){
                triplets.push_back({nums[i], nums[l], nums[r]});
                
                int val1 = nums[l];
                while( l < r && nums[l] == val1) l++;
                    
                
                int val2 = nums[r];
                while(l < r && nums[r] == val2) r--;
                
            }
                
            else if(nums[i] + nums[l] + nums[r]<0)  l++;
                
            else if(nums[i] + nums[l] + nums[r]>0)  r--;
              
        }
    }
    
    return triplets;
}


int main(){
    vector<int> nums1 = {-1,0,1,2,-1,-4};
    vector<vector<int>> triplets = threeSum(nums1);
    for(auto triplet : triplets){
        for(auto e: triplet){
            cout << e << ' ';
        }
        cout << '\n';
    }
    return 0;
}