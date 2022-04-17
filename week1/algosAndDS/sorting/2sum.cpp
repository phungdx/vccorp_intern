#include<iostream>
#include<map>
#include<vector>
using namespace std;

// Solution 1: O(n^2)
// Ta duyệt lần lượt qua mảng, tìm xem 2 số nào có tổng bằng target
// thì trả về index của chùng
vector<int> twoSum_1(vector<int>& nums, int target){
    int remain;
    int n = nums.size(); // size của mảng
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            remain = target - nums[i];
            if(remain == nums[j]){
                return {i, j};
            }
        }
    }
    // Không có cặp nào
    return {-1, -1};
}


// Solution 2: O(n)
// Sử dụng hash map, để keep track được các phần tử đã duyệt qua
// mỗi khi duyệt qua 1 phần tử e nào đó, ta xem phần bù của nó (target - e) đã được
// duyệt qua chưa, nếu rồi thì return lại index của 2 thằng
vector<int> twoSum_2(vector<int>& nums, int target){
    // Lưu phần bù
    int remain;

    int n = nums.size(); // Kích thước mảng

    vector<int> pairs; // lưu index của cặp hợp lệ

    map<int, int> lookup; // keep track các phần tử đã duyệt qua

    for(int i = 0; i < n; ++i){
        remain = target - nums[i]; // phần bù của phần tử đang xét

        if(lookup.find(remain) != lookup.end()){

            // Nếu phần bù đó đã được duyệt qua rồi thì lưu lại index của chúng
            pairs.push_back(lookup.find(remain)->second);
            pairs.push_back(i);
            break;
        }

        // Nếu phần tử bù chưa đc duyệt qua thì lưu lại phần tử đang xét vào hash map
        lookup.insert(pair<int, int> (nums[i], i));
    }
    // return cặp index hợp lệ
    return pairs;
}



int main(){
    vector<int> nums1 = {2,7,11,15};
    vector<int> nums2 = {3,2,4};
    vector<int> num3 = {3,3};
    int target1 = 9;
    int target2 = 6;
    int target3 = 6;
    vector<int> pairs = twoSum_2(nums2, target2);
    for(auto pair: pairs){
        cout << pair <<' ';
    }
    return 0;
}