#include<iostream>
#include<vector>
using namespace std;


// Số cây nhị phân có thể tạo ra được từ 1 số n cho trước tuân theo
// dãy số catalan number

int numTrees(int n){
    vector<int> result(n+1, 0); // Khởi tạo vector với các giá trị ban đầu bằng 0
    result[0] = result[1] = 1; // hai số ban đầu của dãy bằng 1
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < i; ++j){
            result[i] += result[j]* result[i - j - 1]; // số thứ i được tính
        }
    }
    return result[n]; // số thứ n là kết quả cuối cùng;
}


int main(){
    return 0;
}